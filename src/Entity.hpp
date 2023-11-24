#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <SFML/Graphics.hpp>
#include "Spriteinfo.hpp"
#include <string>
#include <iostream>
#include <filesystem>

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
        sf::Vector2f movement(0.f, 0.f);
        movement.x += left ? speed_ : -speed_;

        sf::Vector2f newPos(movement.x + GetPosition().x, GetPosition().y);
        
        // checks if the new position already has an entity in it
        bool canMove = true;
        for (Entity* e : entities_) {
            if (e->GetPosition() == newPos) {   // if there is already an entity in that coordinate, then this entity will remain still
                canMove = false; 
            }
        }
        if (canMove)
            mSprite.move(movement);
    }

    void moveAlongYAxis(bool down) {
        sf::Vector2f movement(0.f, 0.f);
        movement.y += down ? speed_ : -speed_;

        sf::Vector2f newPos(GetPosition().x, movement.y + GetPosition().y);
        
        // checks if the new position already has an entity in it
        bool canMove = true;
        for (Entity* e : entities_) {
            if (e->GetPosition() == newPos) {   // if the new position already has an entity, then this entity will remain still
                canMove = false; 
            }
        }
        if (canMove)
            mSprite.move(movement);
    }

protected:
    sf::Sprite mSprite;
    std::string name_;
    static inline std::vector<Entity*> entities_; // vector to store all entities
    sf::Text text_; // text for current hp level
    const std::string type_;
    int speed_;
    int max_hp_;
    int hitpoints_;
};

#endif // _ENTITY_HPP_