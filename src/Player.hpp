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
    Player(const std::string& name) : Entity("player", 100), inv_(), name_(name)
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

    const std::string& GetName() const { return name_; }
    bool killedBoss() const { return killedBoss_; }

    // returns cooldown progress
    float CooldownProgress() const { 
        if (turnCount_ >= cooldownPeriod_)
            return 1.0f;
        else
            return turnCount_ * 1.0f / cooldownPeriod_; 
    }

    // attacks every monster within 5 tiles
    void rangedAttack() {
        for (Entity* e : entities_) {
            if (e->IsMonster() && distanceBetween(this->GetPosition(), e->GetPosition()) <= 5 * 128) {
                e->takeDamage(20);
            }
        }
    }

    bool drinkHealthPotion() {
        if (inv_.healthPotionCount() >= 1) {
            inv_.addHealthPotions(-1);
            hitpoints_ += 25;
            if (hitpoints_ > max_hp_)
                hitpoints_ = max_hp_;
            return true;
        }
        return false;
    }

    // Handles player input, returns true if the key is valid, false otherwise
    bool processInput(sf::Keyboard::Key key, bool is_pressed) {
        Entity* target = nullptr;
        if (key == sf::Keyboard::E && turnCount_ >= cooldownPeriod_) {   // 10 turn cooldown
            rangedAttack();
            turnCount_ = 0;
            return true;
        }
        else if (key == sf::Keyboard::Q)
            return drinkHealthPotion();
        else if (key == sf::Keyboard::W) 
            target = moveAlongYAxis(false);
        else if (key == sf::Keyboard::S) 
            target = moveAlongYAxis(true);
        else if (key == sf::Keyboard::A) 
            target = moveAlongXAxis(false);
        else if (key == sf::Keyboard::D)
            target = moveAlongXAxis(true);
        else
            return false;
        
        // if a monster is blocking the movement, then the player will attack that monster
        if (target) {
            if (target->IsMonster()) {
                bool died = Attack(target);
                if (target->isBoss() && died) {
                    killedBoss_ = true;
                }
            }
        }
        turnCount_++;
        //std::cout << "Player: " << this->GetPosition().x << ", " << this->GetPosition().y << std::endl;   // prints player location

        return true;
    }

    void checkCollision(int (&level)[120], int &curr_level) {
        if (level[pos_] == 1) {
            inv_.addHealthPotions(1);
            level[pos_] = 0;
        }
        else if (level[pos_] == 3) { // checks that the player on a door tile
            if(pos_ == 59){ //the player on the door leading to the room to the right
                curr_level++;
                pos_ = 3 * 15 + 1;// entrance position
                mSprite.setPosition(128 * (pos_ % TILES_WIDTH), 128 * (pos_ / TILES_WIDTH));
            }
            else if(pos_ == 45){ //the player on the door leading to the room to the left
                curr_level--;
                pos_ =59;// entrance position on the right side
                mSprite.setPosition(128 * (pos_ % TILES_WIDTH), 128 * (pos_ / TILES_WIDTH));
            }
            else if(pos_ == 112){ //the player on the door leading to the room to the dottom
                curr_level = curr_level + 3;
                pos_ = 7;// entrance position on the right side
                mSprite.setPosition(128 * (pos_ % TILES_WIDTH), 128 * (pos_ / TILES_WIDTH));
            }
            else if(pos_ == 7){ //the player on the door leading to the room to the dottom
                curr_level = curr_level - 3;
                pos_ = 113;// entrance position on the right side
                mSprite.setPosition(128 * (pos_ % TILES_WIDTH), 128 * (pos_ / TILES_WIDTH));
            }
        }
        
    }

    void drawInventory(sf::RenderTarget& target) {
        target.draw(inv_);
    }

    private:
        const std::string name_;
        Inventory inv_;
        int turnCount_ = 10;
        int cooldownPeriod_ = 10;
        bool killedBoss_ = false;
};

#endif // PLAYER_H

