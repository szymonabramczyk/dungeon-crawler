#include "Game.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <filesystem>
#include <iostream>

#include "Assets.hpp"
#include "EntityManager.hpp"
#include "Inventory.hpp"
#include "LevelGenerator.hpp"

// Constructor that creates a Window object and creates the Player with the player sprite
// player_speed_ attribute defines the number of pixels
// that the Player moves each time a button is pressed
Game::Game(const std::string& path)
    : window_(sf::VideoMode(1920, 1024), "CMake SFML Project", sf::Style::Titlebar | sf::Style::Close),
      ui_(),
      path_(path) {
    player_ = std::make_shared<Player>("Player");
    EntityManager::AddEntity(player_);
    window_.setSize(sf::Vector2u(1920, 1024));
    window_.setFramerateLimit(144);
    window_.setKeyRepeatEnabled(false);
    LevelGenerator::GenerateLevel(levels_);
    // monsters for level 0
    AddUndead();
    AddUndead();
    AddUndead();
    AddUndead();
}

// A method to Run the game
void Game::Run() {
    sf::Clock clock;
    while (window_.isOpen()) {
        sf::Time delta_time = clock.restart();
        Events();
        Render();
    }
}

// A method to load a level
bool Game::LoadLevel() {
    return map_.Load("tiles", sf::Vector2u(128, 128), levels_[curr_level_], 15, 8);
}

// A method to add monsters
void Game::AddUndead() {
    std::shared_ptr<Monster> undead = std::make_shared<Monster>("undead", 1, 4, 50);
    monsters_.push_back(undead);
    EntityManager::AddEntity(undead);
}

void Game::AddOrc() {
    std::shared_ptr<Monster> orc = std::make_shared<Monster>("orc", 1, 7, 100);
    monsters_.push_back(orc);
    EntityManager::AddEntity(orc);
}

void Game::SpawnMonsters() {
    AddOrc();
    AddOrc();
    AddUndead();
    AddUndead();
    AddUndead();
}

void Game::SpawnBoss() {
    std::shared_ptr<Monster> orc_boss = std::make_shared<Monster>("orc-boss", 2, 32, 300, true);
    monsters_.push_back(orc_boss);
    EntityManager::AddEntity(orc_boss);
}

void Game::DeleteMonsters() {
    monsters_.clear();
    EntityManager::ClearEntities();
    EntityManager::AddEntity(player_);
}

// A method to handle the Events
void Game::Events() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window_.close();
                break;
            case sf::Event::KeyPressed:
                if (!player_->IsDead() && !player_->KilledBoss()) {
                    bool validInput = player_->ProcessInput(event.key.code, true);
                    bool new_level = player_->CheckCollision(levels_[curr_level_], curr_level_);
                    LoadLevel();

                    if (new_level) {
                        DeleteMonsters();
                        auto it = completed_levels_.find(curr_level_);
                        if (curr_level_ == 8) {
                            SpawnBoss();
                        }
                        if (it == completed_levels_.end()) {
                            SpawnMonsters();
                        }
                    } else if (monsters_.empty()) {
                        completed_levels_.insert(curr_level_);
                    } else {
                        auto it = monsters_.begin();
                        if (validInput) {
                            while (it != monsters_.end()) {
                                std::shared_ptr<Monster> monster = *it;
                                if (monster->IsDead()) {
                                    it = monsters_.erase(it);
                                } else {
                                    monster->Update(player_);
                                    it++;
                                }
                            }
                        }
                    }
                }
                Update();
                break;
            case sf::Event::KeyReleased:
                break;
            default:
                break;
        }
    }
}

// A method to Update
void Game::Update() {
    ui_.UpdateHealthUI(player_->GetHitPoints() * 1.0f / player_->MaxHP(),
                       "Health: " + std::to_string(player_->GetHitPoints()) + "/" + std::to_string(player_->MaxHP()));
    ui_.UpdateAbilityUI(player_->CooldownProgress(),
                        std::string("Ability: ") + (player_->IsAbilityReady() ? "Ready" : "Charging..."));
    ui_.UpdateXpUI(player_->LevelProgress(),
                   "Level: " + std::to_string(player_->GetLevel()));

    EntityManager::RemoveDead();

    if (player_->IsDead()) {
        ui_.UpdateEndText(false);
        Assets::sounds["game-over"]->play();
    } else if (player_->KilledBoss()) {
        ui_.UpdateEndText(true);
    }
}

// A method to Render objects to the creen
void Game::Render() {
    window_.clear();
    window_.draw(map_);

    auto it = EntityManager::GetEntities().begin();
    while (it != EntityManager::GetEntities().end()) {  // renders all the living entities and removes the dead ones
        std::shared_ptr<Entity> entity = *it;
        entity->DrawEntity(window_);
        it++;
    }
    for (std::shared_ptr<Monster> monster : monsters_) {  // renders the hp of all monsters
        monster->DrawHitpoints(window_);
    }
    player_->DrawStatus(window_);
    ui_.draw(window_);
    player_->DrawInventory(window_);
    window_.display();
}

int main(int argc, char* argv[]) {
    std::vector<std::string> textures_names = {"player.png", "tiles.png", "orc.png", "health-potion.png", "orc-boss.png", "undead.png", "sword.png"};
    std::vector<std::string> fonts_names = {"Quinquefive-ALoRM.ttf"};
    std::vector<std::string> sounds_names = {"attack.wav", "collect.wav", "chest-open.wav", "level-up.wav", "game-over.wav"};
    try {
        Assets::LoadAssets(argv[0], textures_names, fonts_names, sounds_names);
    } catch (const std::runtime_error& ex) {
        std::cerr << "Error getting loading assets: " << ex.what() << std::endl;
    }

    try {
        // Get the current working directory
        std::filesystem::path current_path = std::filesystem::current_path();

        // Convert the path to a string and print it
        std::cout << "Current working directory: " << current_path.string() << std::endl;
    } catch (const std::filesystem::filesystem_error& ex) {
        std::cerr << "Error getting current working directory: " << ex.what() << std::endl;
    }

    Game game(argv[0]);
    if (!game.LoadLevel())
        std::cout << "there is a problem" << std::endl;
    game.Run();
}