#include "Entity.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>

#include "Assets.hpp"
#include "Constants.hpp"
#include "EntityManager.hpp"

Entity::Entity(const std::string& type, int hp)
    : type_(type), health_points_(hp), max_hp_(hp) {
    // text to display healthpoints above the entity
    text_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    text_.setCharacterSize(16);
    text_.setFillColor(sf::Color::White);
}

// helper function to measure distance between two positions
int Entity::DistanceBetween(const sf::Vector2f& a, const sf::Vector2f& b) {
    sf::Vector2f v = a - b;
    return std::sqrt(v.x * v.x + v.y * v.y);
}

bool Entity::Attack(std::shared_ptr<Entity> target) {
    Assets::sounds["attack"]->play();
    return target->TakeDamage(weapon_damage_);
}

bool Entity::TakeDamage(const int damage) {
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
void Entity::DrawHealthPoints(sf::RenderTarget& target) {
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
void Entity::draw(sf::RenderTarget& target) {
    target.draw(sprite_);
}

std::shared_ptr<Entity> Entity::CheckTile(int pos) {
    std::shared_ptr<Entity> target = nullptr;  // this variable is used to save the entity that prevents this entity from moving

    // checks if the new position already has an entity in it
    for (auto it = EntityManager::begin(); it != EntityManager::end(); ++it) {
        std::shared_ptr<Entity> e = *it;
        if (e->GetTilePosition() == pos) {  // if there is already an entity in that coordinate, then this entity will remain still
            target = e;
            break;
        }
    }
    return target;
}

// Method to move along X and Y axes. Checks for collision and returns a pointer to the entity that is in the way.
std::shared_ptr<Entity> Entity::MoveAlongXAxis(bool left) {
    int new_pos = left ? pos_ + 1 : pos_ - 1;

    bool can_move = true;

    // checks if border of the level is reached
    if (left && pos_ % Constants::kTilesWidth == Constants::kTilesWidth - 1)
        can_move = false;
    if (!left && pos_ % Constants::kTilesWidth == 0)
        can_move = false;

    std::shared_ptr<Entity> target = CheckTile(new_pos);  // this variable is used to save the entity that prevents this entity from moving

    if (target == nullptr && can_move) {
        pos_ = new_pos;
        sprite_.setPosition(128 * (new_pos % Constants::kTilesWidth), 128 * (new_pos / Constants::kTilesWidth));
    }

    return target;
}

// Method to move along X and Y axes. Checks for collision and returns a pointer to the entity that is in the way.
std::shared_ptr<Entity> Entity::MoveAlongYAxis(bool down) {
    int new_pos = down ? pos_ + Constants::kTilesWidth : pos_ - Constants::kTilesWidth;

    bool can_move = true;

    // checks if border of the level is reached
    if (down && pos_ / Constants::kTilesWidth == Constants::kTilesHeight - 1)
        can_move = false;
    if (!down && pos_ / Constants::kTilesWidth == 0)
        can_move = false;

    std::shared_ptr<Entity> target = CheckTile(new_pos);  // this variable is used to save the entity that prevents this entity from moving

    if (target == nullptr && can_move) {
        pos_ = new_pos;
        sprite_.setPosition(128 * (new_pos % Constants::kTilesWidth), 128 * (new_pos / Constants::kTilesWidth));
    }

    return target;
}