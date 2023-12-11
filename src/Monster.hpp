#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include <SFML/Graphics.hpp>
#include <random>

#include "Assets.hpp"
#include "Entity.hpp"

/*! \brief Monster class, inherits from Entity. */
class Monster : public Entity {
   public:
    // Constructor for player class
    // Arguments for Entity(type, speed, hitpoints)
    Monster(const std::string& type, int speed = 1, int damage = 5, int hp = 100, bool is_boss = false);

    ~Monster() {
        // destructor
    }

    /*! function to attack the entity given as argument */
    bool Attack(std::shared_ptr<Entity> target);

    /*! Function that moves the monster towards the player */
    void Update(std::shared_ptr<Entity> player);

   private:
    int speed_;
};

#endif  // MONSTER_HPP_