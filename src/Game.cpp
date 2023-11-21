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
    : window_(sf::VideoMode(1920, 1024), "CMake SFML Project", sf::Style::Titlebar | sf::Style::Close ), 
    player_(Assets::sprites["player"].mTexture),
    player_speed_(128) {
    window_.setSize(sf::Vector2u(1920, 1024)); 
    player_.setScale(0.5, 0.5);
    player_.setPosition(40.f, 500.f);
    window_.setFramerateLimit(144);
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

// A method to handle the events
void Game::events() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window_.close();
                break;
            case sf::Event::KeyPressed:
                processPlayerInput(event.key.code, true); 
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
    window_.draw(player_);
    window_.display();
}

// A method to process player input
void Game::processPlayerInput(sf::Keyboard::Key key, bool is_pressed) {
    if (key == sf::Keyboard::W) 
        moveAlongYAxis(false);
    else if (key == sf::Keyboard::S) 
        moveAlongYAxis(true);
    else if (key == sf::Keyboard::A) 
        moveAlongXAxis(false);
    else if (key == sf::Keyboard::D)
        moveAlongXAxis(true);

}

// Method to move along X and Y axes, should be moved to Player class in the future
void Game::moveAlongXAxis(bool left) {
    sf::Vector2f movement(0.f, 0.f);
    movement.x += left ? player_speed_ : -player_speed_;
    player_.move(movement);
}
void Game::moveAlongYAxis(bool down) {
    sf::Vector2f movement(0.f, 0.f);
    movement.y += down ? player_speed_ : -player_speed_;
    player_.move(movement);
}



int main(int argc, char* argv[]) {
    Assets::loadAssets(argv[0]);

    Game game;
    if(!game.loadLevel(argv[0]))
        std::cout<<"there is a problem"<<std::endl;
    game.run();
}