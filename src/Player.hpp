#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <string>

#include "Entity.hpp"
#include "Inventory.hpp"

// Player class, inherits from Entity
class Player : public Entity {
   public:
    // Constructor for player class
    // Arguments for Entity(name, type, speed, hitpoints)
    Player(const std::string& name);

    ~Player() {
        // destructor
    }

    const std::string& GetName() const { return name_; }
    bool KilledBoss() const { return killed_boss_; }
    bool IsAbilityReady() const { return turn_count_ >= cooldown_period_; }
    int GetLevel() { return level_; }

    void AddXP(int xp);

    void DrawStatus(sf::RenderTarget& target);

    // returns cooldown progress
    float CooldownProgress() const;

    float LevelProgress() const;

    // attacks every monster within 5 tiles
    int RangedAttack();

    bool DrinkHealthPotion();

    // Handles player input, returns true if the key is valid, false otherwise
    bool ProcessInput(sf::Keyboard::Key key, bool is_pressed);

    bool CheckCollision(int (&level)[120], int& curr_level);

    void draw(sf::RenderTarget& target);

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
