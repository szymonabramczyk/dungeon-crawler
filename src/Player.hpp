#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <string>

#include "Assets.hpp"
#include "Entity.hpp"
#include "Inventory.hpp"

// Player class, inherits from Entity
class Player : public Entity {
   public:
    // Constructor for player class
    // Arguments for Entity(name, type, speed, hitpoints)
    Player(const std::string& name) : Entity("player", 100), inv_(), name_(name) {
        pos_ = 3 * 15;
        sprite_ = sf::Sprite(*Assets::textures["player"]);
        sprite_.setPosition(128 * (pos_ % kTilesWidth), 128 * (pos_ / kTilesWidth));
        weapon_damage_ = inv_.GetWeaponDamage();

        status_text_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
        status_text_.setCharacterSize(16);
    }

    ~Player() {
        // destructor
    }

    const std::string& GetName() const { return name_; }
    bool KilledBoss() const { return killed_boss_; }
    bool IsAbilityReady() const { return turn_count_ >= cooldown_period_; }
    int GetLevel() { return level_; }
    void AddXP(int xp) {
        xp_ += xp;
        int new_level = std::floor(xp_ / 200);
        if (new_level > level_) {
            level_ = new_level;
            max_hp_ = 100 + 10 * level_;

            status_text_.setString("Level up!");
            Assets::sounds["level-up"]->play();
            status_text_.setFillColor(sf::Color::Green);
            elapsed_time_ = 0.0f;  // Resets the timer
        }
    }

    void DrawStatus(sf::RenderTarget& target) {
        sf::Vector2f text_position = GetPosition();
        text_position.y -= 30;
        text_position.x -= 20;
        status_text_.setPosition(text_position);

        float dt = clock_.restart().asSeconds();
        elapsed_time_ += dt;

        if (elapsed_time_ <= 2.0f) {  // returns the HP text to white after 0.5 seconds
            target.draw(status_text_);
        }
    }

    // returns cooldown progress
    float CooldownProgress() const {
        if (turn_count_ >= cooldown_period_)
            return 1.0f;
        else
            return turn_count_ * 1.0f / cooldown_period_;
    }

    float LevelProgress() const {
        return (xp_ - (level_ * 200.0f)) / 200;
    }

    // attacks every monster within 5 tiles
    int RangedAttack() {
        int earnedXP = 0;
        for (std::shared_ptr<Entity> e : EntityManager::GetEntities()) {
            if (e->IsMonster() && DistanceBetween(this->GetPosition(), e->GetPosition()) <= 4 * 128) {
                if (e->TakeDamage(20 + 5 * level_)) {
                    if (e->IsBoss())
                        killed_boss_ = true;
                    earnedXP += e->MaxHP();
                }
            }
        }
        return earnedXP;
    }

    bool DrinkHealthPotion() {
        if (inv_.HealthPotionCount() >= 1) {
            inv_.AddHealthPotions(-1);
            hitpoints_ += 25;
            if (hitpoints_ > max_hp_)
                hitpoints_ = max_hp_;
            return true;
        }
        return false;
    }

    // Handles player input, returns true if the key is valid, false otherwise
    bool ProcessInput(sf::Keyboard::Key key, bool is_pressed) {
        std::shared_ptr<Entity> target = nullptr;
        if (key == sf::Keyboard::E && turn_count_ >= cooldown_period_) {  // 10 turn cooldown
            AddXP(RangedAttack());
            turn_count_ = 0;
            return true;
        } else if (key == sf::Keyboard::Q)
            return DrinkHealthPotion();
        else if (key == sf::Keyboard::W)
            target = MoveAlongYAxis(false);
        else if (key == sf::Keyboard::S)
            target = MoveAlongYAxis(true);
        else if (key == sf::Keyboard::A)
            target = MoveAlongXAxis(false);
        else if (key == sf::Keyboard::D)
            target = MoveAlongXAxis(true);
        else
            return false;

        // if a monster is blocking the movement, then the player will attack that monster
        if (target) {
            if (target->IsMonster()) {
                bool died = Attack(target);
                if (target->IsBoss() && died) {
                    killed_boss_ = true;
                }
                if (died) {
                    AddXP(target->MaxHP());
                }
            }
        }
        turn_count_++;
        // std::cout << "Player: " << this->GetPosition().x << ", " << this->GetPosition().y << std::endl;   // prints player location
        // std::cout << "Player: " << this->pos_ << std::endl;
        return true;
    }

    bool CheckCollision(int (&level)[120], int& curr_level) {
        if (level[pos_] == 1) {
            inv_.AddHealthPotions(1);
            Assets::sounds["collect"]->play();
            level[pos_] = 0;
        } else if (level[pos_] == 2) {
            inv_.AddWeaponDamage(5);
            weapon_damage_ = inv_.GetWeaponDamage();
            Assets::sounds["chest-open"]->play();
            level[pos_] = 0;
        } else if (level[pos_] == 3) {  // checks that the player on a door tile
            if (pos_ == 59) {           // the player on the door leading to the room to the right
                curr_level++;
                pos_ = 3 * 15 + 1;  // entrance position
                sprite_.setPosition(128 * (pos_ % kTilesWidth), 128 * (pos_ / kTilesWidth));
            } else if (pos_ == 45) {  // the player on the door leading to the room to the left
                curr_level--;
                pos_ = 59;  // entrance position on the right side
                sprite_.setPosition(128 * (pos_ % kTilesWidth), 128 * (pos_ / kTilesWidth));
            } else if (pos_ == 112) {  // the player on the door leading to the room to the dottom
                curr_level = curr_level + 3;
                pos_ = 7;  // entrance position on the right side
                sprite_.setPosition(128 * (pos_ % kTilesWidth), 128 * (pos_ / kTilesWidth));
            } else if (pos_ == 7) {  // the player on the door leading to the room to the dottom
                curr_level = curr_level - 3;
                pos_ = 113;  // entrance position on the right side
                sprite_.setPosition(128 * (pos_ % kTilesWidth), 128 * (pos_ / kTilesWidth));
            }
            return true;
        }

        return false;
    }

    void DrawInventory(sf::RenderTarget& target) {
        target.draw(inv_);
    }

   private:
    sf::Text status_text_;
    const std::string name_;
    Inventory inv_;
    int turn_count_ = 10;
    int cooldown_period_ = 10;
    bool killed_boss_ = false;
    int xp_ = 0;
    int level_ = 0;

    sf::Clock clock_;
    float elapsed_time_ = 2.0f;  // used for changing the color of the status text
};

#endif  // PLAYER_H_
