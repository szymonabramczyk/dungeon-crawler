#ifndef GAME_HPP_
#define GAME_HPP_

#include "Assets.hpp"
#include "TileMap.hpp"

#include <SFML/Graphics.hpp>

class Game {
    public:
        Game();
        void run();
        bool loadLevel(const std::string& path);

    private:
        void events(); 
        void update(sf::Time delta_time);
        void render();
        void processPlayerInput(sf::Keyboard::Key key, bool isPressed);
        // the following methods should be moved to a Player class
        void moveAlongXAxis(bool left);
        void moveAlongYAxis(bool down);
        
    private:
        sf::RenderWindow window_; 
        sf::Sprite player_;
        int player_speed_;
        int level_[128] =
        {
            0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
            1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
            0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
            0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
            0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
            2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
            0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
        };
        TileMap map_;
        bool is_moving_up_ = false;
        bool is_moving_down_ = false;
        bool is_moving_left_ = false;
        bool is_moving_right_ = false;
};

#endif