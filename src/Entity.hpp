#ifndef ENTITY_HPP_
#define ENTITY_HPP_
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

// Base class for Player and Monster classes
class Entity {
   public:
    Entity(const std::string& type, int hp);
    ~Entity() {}

    // Basic functions to retrieve values
    const std::string& GetType() const { return type_; }
    int GetHealthPoints() const { return health_points_; }
    const sf::Vector2f GetPosition() const { return sprite_.getPosition(); }
    const int MaxHP() const { return max_hp_; }
    bool IsMonster() const { return is_monster_; }
    bool IsDead() const { return is_dead_; }
    bool IsBoss() const { return is_boss_; }
    int GetTilePosition() { return pos_; }

    // helper function to measure distance between two positions
    int DistanceBetween(const sf::Vector2f& a, const sf::Vector2f& b);

    bool Attack(std::shared_ptr<Entity> target);

    bool TakeDamage(const int damage);

    // Renders the hitpoints of the entity
    void DrawHealthPoints(sf::RenderTarget& target);

    // Renders the entity
    void draw(sf::RenderTarget& target);

    // Method to check if there are any Entities on the next tile, to check if can move
    std::shared_ptr<Entity> CheckTile(int pos);

    // Method to move along X and Y axes. Checks for collision and returns a pointer to the entity that is in the way.
    std::shared_ptr<Entity> MoveAlongXAxis(bool left);

    // Method to move along X and Y axes. Checks for collision and returns a pointer to the entity that is in the way.
    std::shared_ptr<Entity> MoveAlongYAxis(bool down);

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