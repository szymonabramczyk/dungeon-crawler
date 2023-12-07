#ifndef GAME_HPP_
#define GAME_HPP_

#include "Assets.hpp"
#include "TileMap.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Entity.hpp"
#include "Inventory.hpp"
#include "UI.hpp"

#include <vector>
#include <random>
#include <set>

#include <SFML/Graphics.hpp>

class Game {
    public:
        Game(const std::string& path);
        void run();
        bool loadLevel();
        
    private:
        void events();
        void addUndead();
        void addOrc();
        void spawnBoss();
        void spawnMonsters();
        void deleteMonsters();
        void update();
        void render();
        
        std::string path_;
        sf::RenderWindow window_; 
        std::shared_ptr<Player> player_;
        std::vector<std::shared_ptr<Monster>> monsters_; // vector to store all monsters

        UI ui_;

        bool gameOver = false;
        
        int levels_ [9][120];
        int curr_level_ = 0;
        std::set<int> completedLevels_;
        TileMap map_;
};

#endif // GAME_HPP_