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
    // Arguments for Entity(name, type, speed, hitpoints)
    Monster(const std::string& name) : Entity(name, "Orc", 128, 100) 
    {
        pos_ = 3 * 15 + 12;
        mSprite = sf::Sprite(Assets::sprites["orc"].mTexture);
        mSprite.setScale(0.50, 0.50);
        mSprite.setPosition(128 * (pos_ % TILES_WIDTH), 128 * (pos_ / TILES_WIDTH));
        isMonster_ = true;
        weaponDamage_ = 5; //temp
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

        // if an entity was blocking movement, then attack the entity (unless it is another monster)
        if (target) {
            if (!target->IsMonster())
                Attack(target);
        }
        // std::cout << name_ << ": " << GetPosition().x << ", " << GetPosition().y << std::endl; // prints the monster location
    }
};

#endif // MONSTER_H