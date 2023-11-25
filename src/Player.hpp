#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include "SpriteInfo.hpp"
#include "Entity.hpp"
#include "Assets.hpp"
#include <string>

// Player class, inherits from Entity
class Player : public Entity {
public:
    // Constructor for player class
    // Arguments for Entity(name, type, speed, hitpoints)
    Player(const std::string& name) : Entity(name, "Player", 128, 100)
    {
        pos_ = 3 * 15;
        mSprite = sf::Sprite(Assets::sprites["player"].mTexture);
        mSprite.setScale(0.5, 0.5);
        mSprite.setPosition(128 * (pos_ % TILES_WIDTH), 128 * (pos_ / TILES_WIDTH));
        weaponDamage_ = 25; //temp
    }

    ~Player()
    {
        //destructor
    }

    // Handles player input
    void processInput(sf::Keyboard::Key key, bool is_pressed) {
        Entity* target = nullptr;
        if (key == sf::Keyboard::W) 
            target = moveAlongYAxis(false);
        else if (key == sf::Keyboard::S) 
            target = moveAlongYAxis(true);
        else if (key == sf::Keyboard::A) 
            target = moveAlongXAxis(false);
        else if (key == sf::Keyboard::D)
            target = moveAlongXAxis(true);
        
        // if a monster is blocking the movement, then the player will attack that monster
        if (target) {
            if (target->IsMonster()) 
                Attack(target);
        }
        //std::cout << "Player: " << this->GetPosition().x << ", " << this->GetPosition().y << std::endl;   // prints player location
    }
};

#endif // PLAYER_H

