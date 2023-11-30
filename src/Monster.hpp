#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include <SFML/Graphics.hpp>
#include "SpriteInfo.hpp"
#include "Entity.hpp"
#include "Assets.hpp"
#include <string>

// Monster class, inherits from Entity
class Monster : public Entity {
public:
    // Constructor for player class
    // Arguments for Entity(type, speed, hitpoints)
    Monster(const std::string& type, int speed = 1, int damage = 5, int hp = 100, bool isBoss = false)
            : Entity(type, hp), speed_(speed)
    {
        pos_ = 3 * 15 + 12;
        mSprite = sf::Sprite(Assets::sprites[type].mTexture);
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
    void update(Entity* player) {
        sf::Vector2f pPos = player->GetPosition(); // player position
        sf::Vector2f mPos = GetPosition(); // monster position

        Entity* target = nullptr;

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

#endif // MONSTER_H