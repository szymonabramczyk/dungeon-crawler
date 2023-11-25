#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <SFML/Graphics.hpp>
#include "Spriteinfo.hpp"
#include <string>
#include <iostream>
#include <filesystem>

#define TILES_WIDTH 15
#define TILES_HEIGHT 8
// Base class for Player and Monster classes
class Entity {
public:
    Entity(const std::string& name, const std::string& type, int speed, int hp)
        : name_(name), type_(type), speed_(speed), hitpoints_(hp), max_hp_(hp) 
    { 
        entities_.push_back(this);  // add this entity to the entities_ vector

        // text to display hitpoints above the entity (sometimes doesn't work, should probably be updated)
        text_.setFont(Assets::fonts["Arial"]);
        text_.setCharacterSize(24);
        text_.setFillColor(sf::Color::White);
    }

    ~Entity() {}

    // Basic functions to retrieve values
    const std::string& GetName() const { return name_; }
    const std::string& GetType() const { return type_; }
    int GetHitPoints() const { return hitpoints_; }
    const sf::Vector2f GetPosition() const { return mSprite.getPosition(); }

    // Renders the entity and its hitpoints on the screen
    void draw(sf::RenderTarget& target)
    {
        // Adjust the value to set the text position above the sprite
        sf::Vector2f textPosition = GetPosition();
        textPosition.y -= 30;
        textPosition.x += 115;
        text_.setPosition(textPosition);
        text_.setString(std::to_string(hitpoints_) + "/" + std::to_string(max_hp_));

        target.draw(mSprite);
        target.draw(text_);
    }


    // Method to move along X and Y axes (checks for collision)
    void moveAlongXAxis(bool left) {
        int new_pos = left ? pos_ + 1 : pos_ - 1;

        bool canMove = true;

        // checks if border of the level is reached
        if (left && pos_ % TILES_WIDTH == TILES_WIDTH - 1)
            canMove = false;
        if (!left && pos_ % TILES_WIDTH == 0)
            canMove = false;

        // checks if the new position already has an entity in it
        for (Entity* e : entities_) {
            if (e->getTilePosition() == new_pos) {   // if there is already an entity in that coordinate, then this entity will remain still
                canMove = false;
                break;
            }
        }
        if (canMove) {
            pos_ = new_pos;
            mSprite.setPosition(128 * (new_pos % TILES_WIDTH), 128 * (new_pos / TILES_WIDTH));
        }
    }

    void moveAlongYAxis(bool down) {
        int new_pos = down ? pos_ + TILES_WIDTH : pos_ - TILES_WIDTH;

        bool canMove = true;

        // checks if border of the level is reached
        if (down && pos_ / TILES_WIDTH == TILES_HEIGHT - 1)
            canMove = false;
        if (!down && pos_ / TILES_WIDTH == 0)
            canMove = false;

        // checks if the new position already has an entity in it
        for (Entity* e : entities_) {
            if (e->getTilePosition() == new_pos) {   // if there is already an entity in that coordinate, then this entity will remain still
                canMove = false; 
            }
        }
        if (canMove) {
            pos_ = new_pos;
            mSprite.setPosition(128 * (new_pos % TILES_WIDTH), 128 * (new_pos / TILES_WIDTH));
        }
    }

    int getTilePosition() {
        return pos_;
    }

protected:
    sf::Sprite mSprite;
    std::string name_;
    static inline std::vector<Entity*> entities_; // vector to store all entities
    sf::Text text_; // text for current hp level
    const std::string type_;
    int speed_;
    int max_hp_;
    int pos_;
    int hitpoints_;
};

#endif // _ENTITY_HPP_