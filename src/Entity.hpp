#ifndef ENTITY_HPP_
#define ENTITY_HPP_
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>

#include "Assets.hpp"
#include "Constants.hpp"
#include "EntityManager.hpp"

// Base class for Player and Monster classes
class Entity {
   public:
    Entity(const std::string& type, int hp)
        : type_(type), health_points_(hp), max_hp_(hp) {
        // text to display hitpoints above the entity
        text_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
        text_.setCharacterSize(16);
        text_.setFillColor(sf::Color::White);
    }

    ~Entity() {}

    // Basic functions to retrieve values
    const std::string& GetType() const { return type_; }
    int GetHitPoints() const { return health_points_; }
    const sf::Vector2f GetPosition() const { return sprite_.getPosition(); }
    const int MaxHP() const { return max_hp_; }
    bool IsMonster() const { return is_monster_; }
    bool IsDead() const { return is_dead_; }
    bool IsBoss() const { return is_boss_; }

    // helper function to measure distance between two positions
    int DistanceBetween(const sf::Vector2f& a, const sf::Vector2f& b) {
        sf::Vector2f v = a - b;
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    bool Attack(std::shared_ptr<Entity> target) {
        Assets::sounds["attack"]->play();
        return target->TakeDamage(weapon_damage_);
    }

    bool TakeDamage(const int damage) {
        if (damage >= health_points_) {
            health_points_ = 0;
            is_dead_ = true;
            Assets::sounds["death"]->play();
            return true;
        } else {
            health_points_ -= damage;
            text_.setFillColor(sf::Color::Red);  // set HP text to red
            elapsed_time_ = 0.0f;                // Resets the timer used to track how long the text is red
            return false;
        }
    }

    // Renders the hitpoints of the entity
    void DrawHitpoints(sf::RenderTarget& target) {
        // Adjust the value to set the text position right above the sprite
        sf::Vector2f text_position = GetPosition();
        text_position.y -= 30;
        text_.setPosition(text_position);
        text_.setString(std::to_string(health_points_) + "/" + std::to_string(max_hp_));

        float dt = clock_.restart().asSeconds();
        elapsed_time_ += dt;

        if (elapsed_time_ >= 0.5f) {  // returns the HP text to white after 0.5 seconds
            text_.setFillColor(sf::Color::White);
        }
        target.draw(text_);
    }

    // Renders the entity
    void DrawEntity(sf::RenderTarget& target) {
        target.draw(sprite_);
    }

    // Method to move along X and Y axes. Checks for collision and returns a pointer to the entity that is in the way.
    std::shared_ptr<Entity> MoveAlongXAxis(bool left) {
        int new_pos = left ? pos_ + 1 : pos_ - 1;

        bool can_move = true;

        // checks if border of the level is reached
        if (left && pos_ % Constants::kTilesWidth == Constants::kTilesWidth - 1)
            can_move = false;
        if (!left && pos_ % Constants::kTilesWidth == 0)
            can_move = false;

        std::shared_ptr<Entity> target = nullptr;  // this variable is used to save the entity that prevents this entity from moving

        // checks if the new position already has an entity in it
        for (auto it = EntityManager::begin(); it != EntityManager::end(); ++it) {
            std::shared_ptr<Entity> e = *it;
            if (e->GetTilePosition() == new_pos) {  // if there is already an entity in that coordinate, then this entity will remain still
                can_move = false;
                target = e;
                break;
            }
        }
        if (can_move) {
            pos_ = new_pos;
            sprite_.setPosition(128 * (new_pos % Constants::kTilesWidth), 128 * (new_pos / Constants::kTilesWidth));
        }

        return target;
    }

    // Method to move along X and Y axes. Checks for collision and returns a pointer to the entity that is in the way.
    std::shared_ptr<Entity> MoveAlongYAxis(bool down) {
        int new_pos = down ? pos_ + Constants::kTilesWidth : pos_ - Constants::kTilesWidth;

        bool can_move = true;

        // checks if border of the level is reached
        if (down && pos_ / Constants::kTilesWidth == Constants::kTilesHeight - 1)
            can_move = false;
        if (!down && pos_ / Constants::kTilesWidth == 0)
            can_move = false;

        std::shared_ptr<Entity> target = nullptr;  // this variable is used to save the entity that prevents this entity from moving

        // checks if the new position already has an entity in it
        for (auto it = EntityManager::begin(); it != EntityManager::end(); ++it) {
            std::shared_ptr<Entity> e = *it;
            if (e->GetTilePosition() == new_pos) {  // if there is already an entity in that coordinate, then this entity will remain still
                can_move = false;
                target = e;
                break;
            }
        }
        if (can_move) {
            pos_ = new_pos;
            sprite_.setPosition(128 * (new_pos % Constants::kTilesWidth), 128 * (new_pos / Constants::kTilesWidth));
        }

        return target;
    }

    int GetTilePosition() {
        return pos_;
    }

   protected:
    sf::Sprite sprite_;
    sf::Text text_;  // text for current hp level
    const std::string type_;
    int speed_;
    int max_hp_;
    int pos_;
    int health_points_;
    bool is_dead_ = false;
    bool is_monster_ = false;
    bool is_boss_;
    int weapon_damage_;  // temporary weapon damage variable (delete when weapon class is implemented)

    int total_turns_ = 0;

    sf::Clock clock_;
    float elapsed_time_ = 0.0f;  // used for changing the color of the HP text
};

#endif  // ENTITY_HPP_