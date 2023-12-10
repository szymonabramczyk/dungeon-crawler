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
    Entity(const std::string& type, int hp);

    ~Entity();

    // Basic functions to retrieve values
    const std::string& GetType() const;
    
    int GetHitPoints() const;
    
    const sf::Vector2f GetPosition() const;
    
    const int MaxHP() const;
    
    bool IsMonster() const;
    
    bool IsDead() const;

    bool IsBoss() const;

    // helper function to measure distance between two positions
    int DistanceBetween(const sf::Vector2f& a, const sf::Vector2f& b);

    bool Attack(std::shared_ptr<Entity> target);

    bool TakeDamage(const int damage);

    // Renders the hitpoints of the entity
    void DrawHitpoints(sf::RenderTarget& target);

    // Renders the entity
    void DrawEntity(sf::RenderTarget& target);

    // Method to move along X and Y axes. Checks for collision and returns a pointer to the entity that is in the way.
    std::shared_ptr<Entity> MoveAlongXAxis(bool left);

    // Method to move along X and Y axes. Checks for collision and returns a pointer to the entity that is in the way.
    std::shared_ptr<Entity> MoveAlongYAxis(bool down);

    int GetTilePosition();

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