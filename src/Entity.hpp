#ifndef ENTITY_HPP_
#define ENTITY_HPP_
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

/*! \brief Abstract class for entities. */
class Entity {
   public:
    Entity(const std::string& type, int hp);
    ~Entity() {}

    /*! Returns the type of the entity (player, orc, undead, etc.) */
    const std::string& GetType() const { return type_; }
    /*! Returns the amount of health points the entity has */
    int GetHealthPoints() const { return health_points_; }
    /*! Returns the current sprite coordinates */
    const sf::Vector2f GetPosition() const { return sprite_.getPosition(); }
    /*! Returns the maximum health points of the entity */
    const int MaxHP() const { return max_hp_; }
    /*! Returns true if the entity is a monster, false otherwise */
    bool IsMonster() const { return is_monster_; }
    /*! Returns true if the entity is dead, false otherwise */
    bool IsDead() const { return is_dead_; }
    /*! Returns true if the entity is a boss, false otherwise */
    bool IsBoss() const { return is_boss_; }
    /*! Returns the tile position of the entity */
    int GetTilePosition() { return pos_; }

    /*! Helper function to measure distance between two positions */
    int DistanceBetween(const sf::Vector2f& a, const sf::Vector2f& b);

    /*! Attacks the entity given as argument */
    bool Attack(std::shared_ptr<Entity> target);

    /*! Removes damage amount of hitpoints from the entity */
    bool TakeDamage(const int damage);

    /*! Renders the hitpoints of the entity */
    void DrawHealthPoints(sf::RenderTarget& target);

    /*! Renders the entity */
    void draw(sf::RenderTarget& target);

    /*! Method to check if there are any Entities on the next tile, to check if can move */
    std::shared_ptr<Entity> CheckTile(int pos);

    /*! Method to move along X and Y axes. Checks for collision and returns a pointer to the entity that is in the way. */
    std::shared_ptr<Entity> MoveAlongXAxis(bool left);

    /*! Method to move along X and Y axes. Checks for collision and returns a pointer to the entity that is in the way. */
    std::shared_ptr<Entity> MoveAlongYAxis(bool down);

   protected:
    sf::Sprite sprite_;
    sf::Text text_;  /*!< text for current hp level */
    const std::string type_;    /*!< type of the entity */
    int speed_;     
    int max_hp_;    
    int pos_;       
    int health_points_; 
    bool is_dead_ = false;
    bool is_monster_ = false;
    bool is_boss_;
    int weapon_damage_;

    int total_turns_ = 0;

    sf::Clock clock_;
    float elapsed_time_ = 0.0f;  /*!< used for changing the color of the HP text */
};

#endif  // ENTITY_HPP_