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
    /*! Constructor that creates a Window object and creates the Player with the player sprite */
    Game(const std::string& path);
    /*! A method to Run the game */
    void Run();
    /*! A method to load a level */
    bool LoadLevel();

   private:
    /*! A method to handle all game events */
    void Events();
    /*! A method to spawn undead monsters */
    void AddUndead();
    /*! A method to spawn orc monsters */
    void AddOrc();
    /*! A method to spawn the monster boss */
    void SpawnBoss();
    /*! A method to spawn a group of monsters */
    void SpawnMonsters();
    /*! A method to delete all monsters */
    void DeleteMonsters();
    /*! A method to update the game */
    void Update();
    /*! A method to render all the assets in the game window */
    void Render();

    std::string path_;
    sf::RenderWindow window_;
    std::shared_ptr<Player> player_;        /*!< Stores the player */
    std::vector<std::shared_ptr<Monster>> monsters_;  /*!<  vector to store all monsters */

    UI ui_;

    int levels_[9][120];
    int curr_level_ = 0;        /*!< Stores current level */
    std::set<int> completed_levels_;    /*!< Stores all the levels the player has beaten */
    TileMap map_;
};

#endif  // GAME_HPP_