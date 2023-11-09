#include "Game.hpp"

#include <SFML/Graphics.hpp>

// Constructor that creates a Window object and creates the Player as a cyan recatngle 
Game::Game() 
    : window_(sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" }), 
    player_(sf::Vector2f(50, 90)),
    player_speed_(500) {
    player_.setFillColor(sf::Color::Cyan);
    player_.setPosition(200.f, 200.f);
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
                processPlayerInput(event.key.code, false); 
                break;
        }
    }
}

// A method to update, 
// currently it just updates the position of the player on the screen
void Game::update(sf::Time delta_time) {
    sf::Vector2f movement(0.f, 0.f); 
    if (is_moving_up_)
        movement.y -= player_speed_; 
    if (is_moving_down_)
        movement.y += player_speed_; 
    if (is_moving_left_)
        movement.x -= player_speed_; 
    if (is_moving_right_)
        movement.x += player_speed_;
    player_.move(movement * delta_time.asSeconds());
}

// A method to render objects to the creen
void Game::render() {
    window_.clear(); 
    window_.draw(player_); 
    window_.display();
}

// A method to change the information about certain keys being pressed 
void Game::processPlayerInput(sf::Keyboard::Key key, bool is_pressed) {
    if (key == sf::Keyboard::W) 
        is_moving_up_ = is_pressed;
    else if (key == sf::Keyboard::S) 
        is_moving_down_ = is_pressed;
    else if (key == sf::Keyboard::A) 
        is_moving_left_ = is_pressed;
    else if (key == sf::Keyboard::D) 
        is_moving_right_ = is_pressed;
}

int main() {
    Game game;
    game.run();
}