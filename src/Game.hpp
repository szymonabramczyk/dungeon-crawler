#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>

class Game {
    public:
        Game();
        void run();

    private:
        void events(); 
        void update(sf::Time delta_time);
        void render();
        void processPlayerInput(sf::Keyboard::Key key, bool isPressed);

    private:
        sf::RenderWindow window_; 
        sf::RectangleShape player_;
        int player_speed_;
        bool is_moving_up_ = false;
        bool is_moving_down_ = false;
        bool is_moving_left_ = false;
        bool is_moving_right_ = false;
};

#endif