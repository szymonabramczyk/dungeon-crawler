#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include <SFML/Graphics.hpp>
#include <random>

#include "Assets.hpp"
#include "Entity.hpp"

// Monster class, inherits from Entity
class Monster : public Entity {
   public:
    // Constructor for player class
    // Arguments for Entity(type, speed, hitpoints)
    Monster(const std::string& type, int speed = 1, int damage = 5, int hp = 100, bool is_boss = false)
        : Entity(type, hp), speed_(speed) {
        bool is_good_pos;
        do {
            // Create a random_device to seed the random number generator
            std::random_device rd;

            // Use the random_device to seed the random number engine
            std::default_random_engine rng(rd());

            // Create a distribution to define the range [0, 14]
            std::uniform_int_distribution<int> x_distribution(0, 14);
            std::uniform_int_distribution<int> y_distribution(0, 7);

            // Generate a random number
            int x = x_distribution(rng);
            int y = y_distribution(rng);

            pos_ = y * Constants::kTilesWidth + x;
            is_good_pos = true;
            for (auto it = EntityManager::begin(); it != EntityManager::end(); ++it) {
                std::shared_ptr<Entity> e = *it;
                if (e->GetTilePosition() == pos_) {
                    is_good_pos = false;
                    break;
                }
            }
            auto it = EntityManager::begin();
            int distance_to_player;
            if (it != EntityManager::end()) {
                distance_to_player =
                    DistanceBetween((*it)->GetPosition(), sf::Vector2f(128 * (pos_ % Constants::kTilesWidth), 128 * (pos_ / Constants::kTilesWidth)));
            }

            if (distance_to_player <= 3 * 128)
                is_good_pos = false;

        } while (!is_good_pos);

        sprite_ = sf::Sprite(*Assets::textures[type]);
        sprite_.setPosition(128 * (pos_ % Constants::kTilesWidth), 128 * (pos_ / Constants::kTilesWidth));
        is_monster_ = true;
        is_boss_ = is_boss;
        weapon_damage_ = damage;  // temp
    }

    ~Monster() {
        // destructor
    }

    bool Attack(std::shared_ptr<Entity> target) {
        if (type_ == "orc") {
            Assets::sounds["orc-attack"]->play();
        } else if (type_ == "boss") {
            Assets::sounds["boss-attack"]->play();
        } else {
            Assets::sounds["monster-attack"]->play();
        }
        return target->TakeDamage(weapon_damage_);
    }

    // Function that moves the monster towards the player
    void Update(std::shared_ptr<Entity> player) {
        sf::Vector2f player_position = player->GetPosition();  // player position
        sf::Vector2f monster_position = GetPosition();         // monster position

        std::shared_ptr<Entity> target = nullptr;

        // check which axis has the largest difference relative to the player location, and then move in that axis
        int x_diff = player_position.x - monster_position.x;
        int y_diff = player_position.y - monster_position.y;

        if (total_turns_ % speed_ == 0) {
            if (abs(x_diff) >= abs(y_diff)) {
                if (player_position.x > monster_position.x)
                    target = MoveAlongXAxis(true);
                else if (player_position.x < monster_position.x)
                    target = MoveAlongXAxis(false);
            } else {
                if (player_position.y > monster_position.y)
                    target = MoveAlongYAxis(true);
                else if (player_position.y < monster_position.y)
                    target = MoveAlongYAxis(false);
            }
        }
        total_turns_++;

        // if an entity was blocking movement, then attack the entity (unless it is another monster)
        if (target) {
            if (!target->IsMonster())
                Attack(target);
        }
        // std::cout << name_ << ": " << GetPosition().x << ", " << GetPosition().y << std::endl; // prints the monster location
    }

   private:
    int speed_;
};

#endif  // MONSTER_HPP_