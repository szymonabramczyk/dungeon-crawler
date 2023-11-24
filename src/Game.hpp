#ifndef GAME_HPP_
#define GAME_HPP_

#include "Assets.hpp"
#include "TileMap.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Entity.hpp"
#include "Inventory.hpp"

#include <SFML/Graphics.hpp>

class Game {
    public:
        Game();
        void run();
        bool loadLevel(const std::string& path);

    private:
        void events();
        void addMonster(const std::string& name);
        void update(sf::Time delta_time);
        void render();
        
    private:
        sf::RenderWindow window_; 
        Player* player_;
        std::vector<Monster*> monsters_; // vector to store all monsters
        std::vector<Entity*> entities_; // vector to store all entities
        int level_[120] =
        {
            0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
            0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };
        TileMap map_;
        Inventory inv_;
};

#endif