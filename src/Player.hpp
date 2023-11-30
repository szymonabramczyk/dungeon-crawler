#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "SpriteInfo.hpp"
#include "Entity.hpp"
#include "Assets.hpp"
#include "Inventory.hpp"
#include "Game.hpp"

#include <string>

#include <SFML/Graphics.hpp>

// Player class, inherits from Entity
class Player : public Entity {
public:
    // Constructor for player class
    // Arguments for Entity(name, type, speed, hitpoints)
    Player(const std::string& name) : Entity(name, "Player", 128, 100), inv_()
    {
        pos_ = 3 * 15;
        mSprite = sf::Sprite(Assets::sprites["player"].mTexture);
        mSprite.setPosition(128 * (pos_ % TILES_WIDTH), 128 * (pos_ / TILES_WIDTH));
        weaponDamage_ = 25; //temp
    }

    ~Player()
    {
        //destructor
    }

    // attacks every monster within 5 tiles
    void rangedAttack() {
        for (Entity* e : entities_) {
            if (e->IsMonster() && distanceBetween(this->GetPosition(), e->GetPosition()) <= 5 * 128) {
                e->takeDamage(20);
            }
        }
    }

    // Handles player input
    void processInput(sf::Keyboard::Key key, bool is_pressed) {
        Entity* target = nullptr;
        if (key == sf::Keyboard::E)
            rangedAttack();
        else if (key == sf::Keyboard::W) 
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

    void checkCollision(int (&level)[120], int &curr_level) {
        if (level[pos_] == 1) {
            inv_.addHealthPotions(1);
            level[pos_] = 0;
        }
        else if (level[pos_] == 3) {
            curr_level++;
            pos_ = 3 * 15;// entrance position
             mSprite.setPosition(128 * (pos_ % TILES_WIDTH), 128 * (pos_ / TILES_WIDTH));
        }
        
    }

    void drawInventory(sf::RenderTarget& target) {
        target.draw(inv_);
    }

    private:
        Inventory inv_;
};

#endif // PLAYER_H

