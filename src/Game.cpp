#include "Game.hpp"
#include "Assets.hpp"

#include <iostream>
#include <filesystem>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp> 

// Constructor that creates a Window object and creates the Player with the player sprite
// player_speed_ attribute defines the number of pixels 
// that the Player moves each time a button is pressed 
Game::Game() 
    : window_(sf::VideoMode(1920, 1024), "CMake SFML Project", sf::Style::Titlebar | sf::Style::Close ) {
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
bool Game::loadLevel(const std::string& path) {
    std::filesystem::path cwd( std::filesystem::canonical( path ) );
    std::filesystem::path file = cwd.parent_path().parent_path() / "tiles.png";
    return map_.load(file.string(), sf::Vector2u(128, 128), level_, 15, 8);
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
                if (event.key.code == sf::Keyboard::T)  // you can spawn new monsters by pressing T
                    addMonster("Orc");
                else {
                    player_->processInput(event.key.code, true);
                    for (Monster* monster : monsters_)
                        monster->update(*player_);
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
    for (Entity* entity : entities_) {    // draws each entity
        entity->draw(window_);
    }
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

    Game game;
    if(!game.loadLevel(argv[0]))
        std::cout<<"there is a problem"<<std::endl;
    game.run();
}