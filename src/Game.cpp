#include "Game.hpp"
#include "Assets.hpp"
#include "Inventory.hpp"

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
    path_(path) {
    player_ = std::make_shared<Player>("Player");
    Entity::entities_.push_back(player_);
    window_.setSize(sf::Vector2u(1920, 1024));
    window_.setFramerateLimit(144);
    window_.setKeyRepeatEnabled(false);

    blackBar_.setFillColor(sf::Color::Black); // Set the initial color
    blackBar_.setSize(sf::Vector2f(205, 20.f));

    healthBar_.setFillColor(sf::Color::Red); // Set the initial color
    healthBar_.setPosition(30, 910); // Adjust the position as needed

    abilityBar_.setFillColor(sf::Color::Yellow); // Set the initial color
    abilityBar_.setPosition(30, 950); // Adjust the position as needed

    xpBar_.setFillColor(sf::Color::Green); // Set the initial color
    xpBar_.setPosition(30, 990); // Adjust the position as needed

    endText_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    endText_.setCharacterSize(85);
    endText_.setFillColor(sf::Color::White);

    infoText_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    infoText_.setCharacterSize(10);
    infoText_.setFillColor(sf::Color::White);

    restartText_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    restartText_.setCharacterSize(25);
    restartText_.setFillColor(sf::Color::White);
    restartText_.setPosition(sf::Vector2f(700, 530));
    //restartText_.setString("Press R to restart");

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
        update(delta_time);
        render();
    }
}

void Game::generatelevel(){
    srand((unsigned) time(NULL));
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 120; j++){
	        levels_[i][j] = 0;
	        int random = rand() % 60;
            if (random < 3){
            levels_[i][j] = random;
            }   
        }
    }
    levels_[0][59] = 3; // setting doors on each level
    levels_[1][45] = 3; 
    levels_[1][59] = 3;
    levels_[2][45] = 3;
    levels_[2][112] = 3;
    levels_[3][59] = 3;
    levels_[4][59] = 3;
    levels_[4][45] = 3;
    levels_[4][112] =3;
    levels_[5][45] = 3;
    levels_[5][7] = 3;
    levels_[6][59] = 3;
    levels_[7][59] = 3;
    levels_[7][45] = 3;
    levels_[7][7] = 3;
}

// A method to load a level
bool Game::loadLevel() {
    return map_.load("tiles", sf::Vector2u(128, 128), levels_[curr_level_], 15, 8);
}

// A method to add monsters
void Game::addUndead() {
    std::shared_ptr<Monster> undead = std::make_shared<Monster>("undead", 1, 4, 50);
    monsters_.push_back(undead);
    Entity::entities_.push_back(undead);
}

void Game::addOrc() {
    std::shared_ptr<Monster> orc = std::make_shared<Monster>("orc", 1, 7, 100);
    monsters_.push_back(orc);
    Entity::entities_.push_back(orc);
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
    Entity::entities_.push_back(orcBoss);
}

void Game::deleteMonsters() {
    monsters_.clear();
    Entity::entities_.clear();
    Entity::entities_.push_back(player_);
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
                // Assets::sounds["attack"]->play();
                if (event.key.code == sf::Keyboard::Up) // you can add potions using up arrow
                    {}// inv_.addHealthPotions(1);
                if (event.key.code == sf::Keyboard::Down) // you can remove potions using down arrow
                    {}// inv_.addHealthPotions(-1);
                
                else if (!player_->IsDead() && !player_->killedBoss()) {
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
                break;
            case sf::Event::KeyReleased:
                break;
            default:
                break;
        }
    }
}

// A method to update
void Game::update(sf::Time delta_time) {
}

// A method to render objects to the creen
void Game::render() {
    window_.clear(); 
    window_.draw(map_); 

    auto it = Entity::entities_.begin();
    while (it != Entity::entities_.end()) {   // renders all the living entities and removes the dead ones
        std::shared_ptr<Entity> entity = *it;
        if (entity->IsDead()) {
            it = Entity::entities_.erase(it);
        } else {
            entity->drawEntity(window_);
            it++;
        }
    }
    for (std::shared_ptr<Monster> monster : monsters_) {  // renders the hp of all monsters
        monster->drawHitpoints(window_);
    }
    player_->drawStatus(window_);
    
    blackBar_.setPosition(30, 910); // Adjust the position as needed
    window_.draw(blackBar_);
    healthBar_.setSize(sf::Vector2f(player_->GetHitPoints() * 1.0f / player_->maxHP() *200, 15.f));
    window_.draw(healthBar_);

    blackBar_.setPosition(30, 950); // Adjust the position as needed
    window_.draw(blackBar_);
    abilityBar_.setSize(sf::Vector2f(player_->CooldownProgress()*200.f, 15.f));
    window_.draw(abilityBar_);

    blackBar_.setPosition(30, 990); // Adjust the position as needed
    window_.draw(blackBar_);
    xpBar_.setSize(sf::Vector2f(player_->LevelProgress()*200.f, 15.f));
    window_.draw(xpBar_);

    infoText_.setString("Health:" + std::to_string(player_->GetHitPoints()) + "/" + std::to_string(player_->maxHP()));
    infoText_.setPosition(30, 890);
    window_.draw(infoText_);
    infoText_.setString(std::string("Ability: ") + (player_->abilityReady() ? "Ready" : "Charging..."));
    infoText_.setPosition(30, 932);
    window_.draw(infoText_);
    infoText_.setString("Level: " + std::to_string(player_->getLevel()));
    infoText_.setPosition(30, 972);
    window_.draw(infoText_);

    player_->drawInventory(window_);

    // !!! this should not be here !!!
    if (player_->IsDead()) {
        endText_.setPosition(sf::Vector2f(500, 384));
        endText_.setString("Game Over!");
        Assets::sounds["game-over"]->play();
        window_.draw(endText_);
        window_.draw(restartText_);
    }
    else if (player_->killedBoss()) {
        endText_.setPosition(sf::Vector2f(575, 384));
        endText_.setString("Victory!");
        window_.draw(endText_);
        window_.draw(restartText_);
    }

    window_.display();
}

int main(int argc, char* argv[]) {
    try {
        Assets::loadAssets(argv[0]);
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
    game.generatelevel();
    if(!game.loadLevel())
        std::cout<<"there is a problem"<<std::endl;
    game.run();
}