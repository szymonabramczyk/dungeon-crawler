#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_
#include "SpriteInfo.hpp"
#include "Assets.hpp"

#include <string>
#include <iostream>
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Base class for Player and Monster classes
class Entity {
public:
    static inline std::vector<std::shared_ptr<Entity>> entities_; // vector to store all entities

    Entity(const std::string& type, int hp)
        : type_(type), hitpoints_(hp), max_hp_(hp) 
    { 
        // entities_.push_back(std::make_shared<Entity>(this));  // add this entity to the entities_ vector

        // text to display hitpoints above the entity
        text_.setFont(Assets::fonts["Quinquefive-ALoRM"]);
        text_.setCharacterSize(16);
        text_.setFillColor(sf::Color::White);
    }

    ~Entity() {}

    // Basic functions to retrieve values
    const std::string& GetType() const { return type_; }
    int GetHitPoints() const { return hitpoints_; }
    const sf::Vector2f GetPosition() const { return mSprite.getPosition(); }
    bool IsMonster() const { return isMonster_; }
    bool IsDead() const { return isDead_; }
    bool isBoss() const { return isBoss_; }

    // helper function to measure distance between two positions
    int distanceBetween(const sf::Vector2f& a, const sf::Vector2f& b) {
        sf::Vector2f v = a - b;
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    bool Attack(std::shared_ptr<Entity> target) {
        Assets::sounds["attack"]->play();
        return target->takeDamage(weaponDamage_);
    }

    bool takeDamage(const int damage) {
        if (damage >= hitpoints_) {
            hitpoints_ = 0;
            isDead_ = true;
            // Remove the entity from the entities_ vector if it dies
            auto it = std::find_if(entities_.begin(), entities_.end(), 
                [this](const std::shared_ptr<Entity>& entity) {
                return entity.get() == this;
                });
            if (it != entities_.end()) {
                entities_.erase(it);
            }
            return true;
        } else {
            hitpoints_ -= damage;
            text_.setFillColor(sf::Color::Red);    // set HP text to red
            elapsedTime_ = 0.0f;  // Resets the timer used to track how long the text is red
            return false;
        }

    }

    // Renders the hitpoints of the entity
    void drawHitpoints(sf::RenderTarget& target)
    {
        // Adjust the value to set the text position right above the sprite
        sf::Vector2f textPosition = GetPosition();
        textPosition.y -= 30;
        //textPosition.x += 80;
        text_.setPosition(textPosition);
        text_.setString(std::to_string(hitpoints_) + "/" + std::to_string(max_hp_));

        float dt = clock_.restart().asSeconds();
        elapsedTime_ += dt;

        if (elapsedTime_ >= 0.5f) {     // returns the HP text to white after 0.5 seconds
            text_.setFillColor(sf::Color::White);
        }
        target.draw(text_);
    }

    // Renders the entity
    void drawEntity(sf::RenderTarget& target)
    {
        target.draw(mSprite);
    }


    // Method to move along X and Y axes. Checks for collision and returns a pointer to the entity that is in the way.
    std::shared_ptr<Entity> moveAlongXAxis(bool left) {
        int new_pos = left ? pos_ + 1 : pos_ - 1;

        bool canMove = true;

        // checks if border of the level is reached
        if (left && pos_ % TILES_WIDTH == TILES_WIDTH - 1)
            canMove = false;
        if (!left && pos_ % TILES_WIDTH == 0)
            canMove = false;

        std::shared_ptr<Entity> target = nullptr;  // this variable is used to save the entity that prevents this entity from moving

        // TO IMPLEMENT
        // should check if the new tile is a floor or a door tile
        // a Level class should probably be created and get a current level from there
        // and check the type of tile
        // if (new_pos != 0 && new_pos != 3) 
        //     canMove = false;

        // checks if the new position already has an entity in it
        for (std::shared_ptr<Entity> e : entities_) {
            if (e->getTilePosition() == new_pos) {   // if there is already an entity in that coordinate, then this entity will remain still
                canMove = false;
                target = e;
                break;
            }
        }
        if (canMove) {
            pos_ = new_pos;
            mSprite.setPosition(128 * (new_pos % TILES_WIDTH), 128 * (new_pos / TILES_WIDTH));
        }

        return target;
    }

    // Method to move along X and Y axes. Checks for collision and returns a pointer to the entity that is in the way.
    std::shared_ptr<Entity> moveAlongYAxis(bool down) {
        int new_pos = down ? pos_ + TILES_WIDTH : pos_ - TILES_WIDTH;

        bool canMove = true;

        // checks if border of the level is reached
        if (down && pos_ / TILES_WIDTH == TILES_HEIGHT - 1)
            canMove = false;
        if (!down && pos_ / TILES_WIDTH == 0)
            canMove = false;
            
        std::shared_ptr<Entity> target = nullptr;  // this variable is used to save the entity that prevents this entity from moving

        // checks if the new position already has an entity in it
        for (std::shared_ptr<Entity> e : entities_) {
            if (e->getTilePosition() == new_pos) {   // if there is already an entity in that coordinate, then this entity will remain still
                canMove = false; 
                target = e;
                break;
            }
        }
        if (canMove) {
            pos_ = new_pos;
            mSprite.setPosition(128 * (new_pos % TILES_WIDTH), 128 * (new_pos / TILES_WIDTH));
        }

        return target;
    }

    int getTilePosition() {
        return pos_;
    }

protected:
    sf::Sprite mSprite;
    sf::Text text_; // text for current hp level
    const std::string type_;
    int speed_;
    int max_hp_;
    int pos_;
    int hitpoints_;
    bool isDead_ = false;
    bool isMonster_ = false;
    bool isBoss_;
    int weaponDamage_; // temporary weapon damage variable (delete when weapon class is implemented)

    int totalTurns_ = 0;

    sf::Clock clock_;
    float elapsedTime_ = 0.0f;  // used for changing the color of the HP text

    const int TILES_WIDTH = 15;
    const int TILES_HEIGHT = 8;
};

#endif // _ENTITY_HPP_