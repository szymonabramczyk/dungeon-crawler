#ifndef PLAYER_HPP_
#define PLAYER_HPP_

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
        mSprite = sf::Sprite(*Assets::textures["player"]);
        mSprite.setPosition(128 * (pos_ % TILES_WIDTH), 128 * (pos_ / TILES_WIDTH));
        weaponDamage_ = 25; //temp

        statusText_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
        statusText_.setCharacterSize(16);
    }

    ~Player()
    {
        //destructor
    }

    const std::string& GetName() const { return name_; }
    bool killedBoss() const { return killedBoss_; }
    bool abilityReady() const { return turnCount_ >= cooldownPeriod_; }
    int getLevel() { return level_; }
    void addXP(int xp) { 
        xp_ += xp; 
        int newLevel = std::floor(xp_ / 200);
        if (newLevel > level_) {
            level_ = newLevel;
            max_hp_ = 100 + 10 * level_;

            statusText_.setString("Level up!");
            Assets::sounds["level-up"]->play();
            statusText_.setFillColor(sf::Color::Green);
            elapsedTime_ = 0.0f;  // Resets the timer
        }
    }

    void drawStatus(sf::RenderTarget& target) {
        sf::Vector2f textPosition = GetPosition();
        textPosition.y -= 30;
        textPosition.x -= 20;
        statusText_.setPosition(textPosition);

        float dt = clock_.restart().asSeconds();
        elapsedTime_ += dt;

        if (elapsedTime_ <= 2.0f) {     // returns the HP text to white after 0.5 seconds
            target.draw(statusText_);
        }
    }

    // returns cooldown progress
    float CooldownProgress() const { 
        if (turnCount_ >= cooldownPeriod_)
            return 1.0f;
        else
            return turnCount_ * 1.0f / cooldownPeriod_; 
    }

    float LevelProgress() const {
        return (xp_ - (level_ * 200.0f)) / 200;
    }

    // attacks every monster within 5 tiles
    int rangedAttack() {
        int earnedXP = 0;
        for (std::shared_ptr<Entity> e : entities_) {
            if (e->IsMonster() && distanceBetween(this->GetPosition(), e->GetPosition()) <= 4 * 128) {
                if (e->takeDamage(20 + 5 * level_)) {
                    if (e->isBoss()) 
                        killedBoss_ = true;
                    earnedXP += e->maxHP();
                }
            }
        }
        return earnedXP;
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
        std::shared_ptr<Entity> target = nullptr;
        if (key == sf::Keyboard::E && turnCount_ >= cooldownPeriod_) {   // 10 turn cooldown
            addXP(rangedAttack());
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
                if (died) {
                    addXP(target->maxHP());
                }
            }
        }
        turnCount_++;
        //std::cout << "Player: " << this->GetPosition().x << ", " << this->GetPosition().y << std::endl;   // prints player location
        //std::cout << "Player: " << this->pos_ << std::endl;
        return true;
    }

    bool checkCollision(int (&level)[120], int &curr_level) {
        if (level[pos_] == 1) {
            inv_.addHealthPotions(1);
            Assets::sounds["collect"]->play();
            level[pos_] = 0;
        }
        else if (level[pos_] == 2) {
            Assets::sounds["chest-open"]->play();
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
            return true;
        }
        
        return false;
    }

    void drawInventory(sf::RenderTarget& target) {
        target.draw(inv_);
    }

    private:
        sf::Text statusText_;
        const std::string name_;
        Inventory inv_;
        int turnCount_ = 10;
        int cooldownPeriod_ = 10;
        bool killedBoss_ = false;
        int xp_ = 0;
        int level_ = 0;

        sf::Clock clock_;
        float elapsedTime_ = 2.0f;  // used for changing the color of the status text
};

#endif // PLAYER_H

