#include "Game.hpp"
#include "Assets.hpp"
#include "Inventory.hpp"

#include <iostream>
#include <filesystem>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp> 

// Constructor that creates a Window object and creates the Player with the player sprite
// player_speed_ attribute defines the number of pixels 
// that the Player moves each time a button is pressed 
Game::Game(const std::string& path) 
    : window_(sf::VideoMode(1920, 1024), "CMake SFML Project", sf::Style::Titlebar | sf::Style::Close ),
    path_(path) {
    player_ = new Player("Player"); 
    entities_.push_back(player_);
    window_.setSize(sf::Vector2u(1920, 1024));
    window_.setFramerateLimit(144);
    addMonster("Orc"); 
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


// A method to load a level
bool Game::loadLevel() {
    std::filesystem::path cwd( std::filesystem::canonical( path_ ) );
    std::filesystem::path file = cwd.parent_path().parent_path() / "tiles.png";
    return map_.load(file.string(), sf::Vector2u(128, 128), levels_[curr_level_], 15, 8);
}

// A method to add monsters
void Game::addMonster(const std::string& name) {
    Monster* monster = new Monster(name);
    monsters_.push_back(monster);
    entities_.push_back(monster);
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
                if (event.key.code == sf::Keyboard::Up) // you can add potions using up arrow
                    {}// inv_.addHealthPotions(1);
                if (event.key.code == sf::Keyboard::Down) // you can remove potions using down arrow
                    {}// inv_.addHealthPotions(-1);
                if (event.key.code == sf::Keyboard::T)  // you can spawn new monsters by pressing T
                    addMonster("Orc");
                        

                
                else {
                    player_->processInput(event.key.code, true);
                    player_->checkCollision(levels_[curr_level_]);
                    loadLevel();
                    auto it = monsters_.begin();
                    while (it != monsters_.end()) {
                        Monster* monster = *it;
                        if (monster->IsDead()) {
                            it = monsters_.erase(it);
                        } else {
                            monster->update(player_);
                            it++;
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

    auto it = entities_.begin();
    while (it != entities_.end()) {   // renders all the living entities and removes the dead ones
        Entity* entity = *it;
        if (entity->IsDead()) {
            it = entities_.erase(it);
        } else {
            entity->drawEntity(window_);
            it++;
        }
    }
    for (Entity* entity : entities_) {  // renders the hp of all entities
        entity->drawHitpoints(window_);
    }
    player_->drawInventory(window_);
    window_.display();
}

int main(int argc, char* argv[]) {
    Assets::loadAssets(argv[0]);

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