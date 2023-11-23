#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include "Spriteinfo.hpp"
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
        mSprite = sf::Sprite(Assets::sprites["player"].mTexture);
        mSprite.setScale(0.5, 0.5);
        mSprite.setPosition(808.f, 756.f);
    }

    ~Player()
    {
        //destructor
    }

    // Handles player input
    void processInput(sf::Keyboard::Key key, bool is_pressed) {
        if (key == sf::Keyboard::W) 
            moveAlongYAxis(false);
        else if (key == sf::Keyboard::S) 
            moveAlongYAxis(true);
        else if (key == sf::Keyboard::A) 
            moveAlongXAxis(false);
        else if (key == sf::Keyboard::D)
            moveAlongXAxis(true);
        //std::cout << "Player: " << this->GetPosition().x << ", " << this->GetPosition().y << std::endl;   // prints player location
    }
};

#endif // PLAYER_H

