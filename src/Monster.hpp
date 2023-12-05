#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Assets.hpp"
#include <random>

// Monster class, inherits from Entity
class Monster : public Entity {
public:
    // Constructor for player class
    // Arguments for Entity(type, speed, hitpoints)
    Monster(const std::string& type, int speed = 1, int damage = 5, int hp = 100, bool isBoss = false)
            : Entity(type, hp), speed_(speed)
    {
        bool isGoodPos;
        do {
            // Create a random_device to seed the random number generator
            std::random_device rd;

            // Use the random_device to seed the random number engine
            std::default_random_engine rng(rd());

            // Create a distribution to define the range [0, 14]
            std::uniform_int_distribution<int> xDistribution(0, 14);
            std::uniform_int_distribution<int> yDistribution(0, 7);

            // Generate a random number
            int x = xDistribution(rng);
            int y = yDistribution(rng);

            pos_ = y * 15 + x;
            isGoodPos = true;
            for (std::shared_ptr<Entity> e : entities_) {
                if (e->getTilePosition() == pos_) {   // if there is already an entity in that coordinate, then this entity will remain still
                    isGoodPos = false;
                    break;
                }
            }

            int distanceToPlayer = 
                distanceBetween(entities_[0]->GetPosition(), sf::Vector2f(128*(pos_ % TILES_WIDTH), 128*(pos_ / TILES_WIDTH)));

            if (distanceToPlayer <= 3 * 128)
                isGoodPos = false;

        } while (!isGoodPos);

        mSprite = sf::Sprite(*Assets::textures[type]);
        mSprite.setPosition(128 * (pos_ % TILES_WIDTH), 128 * (pos_ / TILES_WIDTH));
        isMonster_ = true;
        isBoss_ = isBoss;
        weaponDamage_ = damage; //temp
    }

    ~Monster()
    {
        //destructor
    }

    // Function that moves the monster towards the player
    void update(std::shared_ptr<Entity> player) {
        sf::Vector2f pPos = player->GetPosition(); // player position
        sf::Vector2f mPos = GetPosition(); // monster position

        std::shared_ptr<Entity> target = nullptr;

        // check which axis has the largest difference relative to the player location, and then move in that axis
        int xDiff = pPos.x - mPos.x;
        int yDiff = pPos.y - mPos.y;

        if (totalTurns_ % speed_ == 0) {
            if (abs(xDiff) >= abs(yDiff)) {
                if (pPos.x > mPos.x) 
                    target = moveAlongXAxis(true);
                else if (pPos.x < mPos.x)
                    target = moveAlongXAxis(false);
            } else {
                if (pPos.y > mPos.y) 
                    target = moveAlongYAxis(true);
                else if (pPos.y < mPos.y)
                    target = moveAlongYAxis(false); 
            }
        }
        totalTurns_++;

        // if an entity was blocking movement, then attack the entity (unless it is another monster)
        if (target) {
            if (!target->IsMonster())
                Attack(target);
        }
        // std::cout << name_ << ": " << GetPosition().x << ", " << GetPosition().y << std::endl; // prints the monster location
    }

    private:
        int speed_;
};

#endif // MONSTER_HPP_