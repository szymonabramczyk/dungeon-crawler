#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>

class Game {
    public:
        Game();
        void run();

    private:
        void events(); 
        void update();
        void render();

    private:
        sf::RenderWindow window_; 
        sf::RectangleShape player_;
};

#endif