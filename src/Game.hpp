#ifndef GAME_HPP_
#define GAME_HPP_

#include "Assets.hpp"
#include "TileMap.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Entity.hpp"
#include "Inventory.hpp"
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

class Game {
    public:
        Game(const std::string& path);
        void run();
        void makelevels();
        bool loadLevel();
        void generatelevel();
        


    private:
        void events();
        void addUndead();
        void addOrc();
        void addOrcBoss();
        void update(sf::Time delta_time);
        void render();
        
    private:
        std::string path_;
        sf::RenderWindow window_; 
        std::shared_ptr<Player> player_;
        std::vector<std::shared_ptr<Monster>> monsters_; // vector to store all monsters

        sf::RectangleShape healthBar_;
        sf::RectangleShape abilityBar_;
        sf::RectangleShape xpBar_;
        sf::RectangleShape blackBar_;

        sf::Text endText_;
        sf::Text restartText_;
        sf::Text infoText_;

        bool gameOver = false;
        

        int levels_ [9][120];
        int curr_level_ = 0;
        TileMap map_;
        friend class Player;
};

#endif