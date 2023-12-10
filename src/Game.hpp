#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include <random>
#include <set>
#include <vector>

#include "Assets.hpp"
#include "Entity.hpp"
#include "Inventory.hpp"
#include "Monster.hpp"
#include "Player.hpp"
#include "TileMap.hpp"
#include "UI.hpp"

/*! \brief Class for the game. */
class Game {
   public:
    Game(const std::string& path);
    void Run();
    bool LoadLevel();

   private:
    void Events();
    void AddUndead();
    void AddOrc();
    void SpawnBoss();
    void SpawnMonsters();
    void DeleteMonsters();
    void Update();
    void Render();

    std::string path_;
    sf::RenderWindow window_;
    std::shared_ptr<Player> player_;
    std::vector<std::shared_ptr<Monster>> monsters_;  // vector to store all monsters

    UI ui_;

    int levels_[9][120];
    int curr_level_ = 0;
    std::set<int> completed_levels_;
    TileMap map_;
};

#endif  // GAME_HPP_