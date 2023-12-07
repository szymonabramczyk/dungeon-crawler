#include "Game.hpp"
#include "Assets.hpp"
#include "Inventory.hpp"
#include "LevelGenerator.hpp"
#include "EntityManager.hpp"

#include <iostream>
#include <filesystem>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp> 
#include <SFML/Audio.hpp>

// Constructor that creates a Window object and creates the Player with the player sprite
// player_speed_ attribute defines the number of pixels 
// that the Player moves each time a button is pressed 
Game::Game(const std::string& path) 
    : window_(sf::VideoMode(1920, 1024), "CMake SFML Project", sf::Style::Titlebar | sf::Style::Close ),
    ui_(),
    path_(path) {
    player_ = std::make_shared<Player>("Player");
    EntityManager::addEntity(player_);
    window_.setSize(sf::Vector2u(1920, 1024));
    window_.setFramerateLimit(144);
    window_.setKeyRepeatEnabled(false);
    LevelGenerator::generateLevel(levels_);
    // monsters for level 0
    addUndead();
    addUndead();
    addUndead();
    addUndead();
}

// A method to run the game
void Game::run() {
    sf::Clock clock;
    while (window_.isOpen()) {
        sf::Time delta_time = clock.restart();
        events();
        render();
    }
}

// A method to load a level
bool Game::loadLevel() {
    return map_.load("tiles", sf::Vector2u(128, 128), levels_[curr_level_], 15, 8);
}

// A method to add monsters
void Game::addUndead() {
    std::shared_ptr<Monster> undead = std::make_shared<Monster>("undead", 1, 4, 50);
    monsters_.push_back(undead);
    EntityManager::addEntity(undead);
}

void Game::addOrc() {
    std::shared_ptr<Monster> orc = std::make_shared<Monster>("orc", 1, 7, 100);
    monsters_.push_back(orc);
    EntityManager::addEntity(orc);
}

void Game::spawnMonsters() {
    addOrc();
    addOrc();
    addUndead();
    addUndead();
    addUndead();
}

void Game::spawnBoss() {
    std::shared_ptr<Monster> orcBoss = std::make_shared<Monster>("orc-boss", 2, 32, 300, true);
    monsters_.push_back(orcBoss);
    EntityManager::addEntity(orcBoss);
}

void Game::deleteMonsters() {
    monsters_.clear();
    EntityManager::clearEntities();
    EntityManager::addEntity(player_);
}

// A method to handle the events
void Game::events() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window_.close();
                break;
            case sf::Event::KeyPressed:
                if (!player_->IsDead() && !player_->killedBoss()) {
                    bool validInput = player_->processInput(event.key.code, true);
                    bool newLevel = player_->checkCollision(levels_[curr_level_], curr_level_);
                    loadLevel();

                    if (newLevel) {
                        deleteMonsters();
                        auto it = completedLevels_.find(curr_level_);
                        if (curr_level_ == 8) {
                            spawnBoss();
                        } if (it == completedLevels_.end()) {
                            spawnMonsters();
                        }
                    }
                    else if (monsters_.empty()) {
                        completedLevels_.insert(curr_level_);
                    } 
                    else {
                        auto it = monsters_.begin();
                        if (validInput) {
                            while (it != monsters_.end()) {
                                std::shared_ptr<Monster> monster = *it;
                                if (monster->IsDead()) {
                                    it = monsters_.erase(it);
                                } else {
                                    monster->update(player_);
                                    it++;
                                }
                            }
                        }
                    }
                }
                update();
                break;
            case sf::Event::KeyReleased:
                break;
            default:
                break;
        }
    }
}

// A method to update
void Game::update() {
    
    ui_.updateHealthUI(player_->GetHitPoints() * 1.0f / player_->maxHP(),
            "Health: " + std::to_string(player_->GetHitPoints()) + "/" + std::to_string(player_->maxHP()));
    ui_.updateAbilityUI(player_->CooldownProgress(),
            std::string("Ability: ") + (player_->abilityReady() ? "Ready" : "Charging..."));
    ui_.updateXpUI(player_->LevelProgress(),
            "Level: " + std::to_string(player_->getLevel()));

    EntityManager::removeDead();

    if (player_->IsDead()) {
        ui_.updateEndText(false);
        Assets::sounds["game-over"]->play();
    }
    else if (player_->killedBoss()) {
        ui_.updateEndText(true);
    }
}

// A method to render objects to the creen
void Game::render() {
    window_.clear(); 
    window_.draw(map_); 

    auto it = EntityManager::getEntities().begin();
    while (it != EntityManager::getEntities().end()) {   // renders all the living entities and removes the dead ones
        std::shared_ptr<Entity> entity = *it;
        entity->drawEntity(window_);
        it++;
    }
    for (std::shared_ptr<Monster> monster : monsters_) {  // renders the hp of all monsters
        monster->drawHitpoints(window_);
    }
    player_->drawStatus(window_);
    ui_.draw(window_);
    player_->drawInventory(window_);
    window_.display();
}

int main(int argc, char* argv[]) {
    std::vector<std::string> textures_names = {"player.png", "tiles.png", "orc.png", "health-potion.png", "orc-boss.png", "undead.png", "sword.png"};
    std::vector<std::string> fonts_names = {"Quinquefive-ALoRM.ttf"};
    std::vector<std::string> sounds_names = {"attack.wav", "collect.wav", "chest-open.wav", "level-up.wav", "game-over.wav"};
    try {
        Assets::loadAssets(argv[0], textures_names, fonts_names, sounds_names);
    } catch (const std::runtime_error& ex) {
        std::cerr << "Error getting loading assets: " << ex.what() << std::endl;
    }

    try {
        // Get the current working directory
        std::filesystem::path currentPath = std::filesystem::current_path();

        // Convert the path to a string and print it
        std::cout << "Current working directory: " << currentPath.string() << std::endl;
    } catch (const std::filesystem::filesystem_error& ex) {
        std::cerr << "Error getting current working directory: " << ex.what() << std::endl;
    }

    Game game(argv[0]);
    if(!game.loadLevel())
        std::cout<<"there is a problem"<<std::endl;
    game.run();
}