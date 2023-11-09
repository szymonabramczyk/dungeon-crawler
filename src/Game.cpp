#include "Game.hpp"

#include <SFML/Graphics.hpp>

// Constructor that creates a Window object and creates the Player as a cyan recatngle 
Game::Game() 
    : window_(sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" }), 
    player_(sf::Vector2f(120, 50)) {
    player_.setFillColor(sf::Color::Cyan);
    window_.setFramerateLimit(144);
}

// A method to run the game
void Game::run() {
    while (window_.isOpen()) {
        events();
        update();
        render();
    }
}

// A method to handle the events
void Game::events() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
    }
}

void Game::update() {

}

// A method to render objects to the creen
void Game::render() {
    window_.clear(); 
    window_.draw(player_); 
    window_.display();
}

int main() {
    Game game;
    game.run();
}