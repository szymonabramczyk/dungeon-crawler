#include "Player.hpp"

#include <SFML/Graphics.hpp>
#include <string>

#include "Assets.hpp"
#include "Constants.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Inventory.hpp"

// Constructor for player class
// Arguments for Entity(name, type, speed, hitpoints)
Player::Player(const std::string& name) : Entity("player", 100), inv_(), name_(name) {
    pos_ = 3 * Constants::kTilesWidth;
    sprite_ = sf::Sprite(*Assets::textures["player"]);
    sprite_.setPosition(128 * (pos_ % Constants::kTilesWidth), 128 * (pos_ / Constants::kTilesWidth));
    weapon_damage_ = inv_.GetWeaponDamage();

    status_text_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    status_text_.setCharacterSize(16);
}

void Player::AddXP(int xp) {
    xp_ += xp;
    int new_level = std::floor(xp_ / 200);
    if (new_level > level_) {
        level_ = new_level;
        max_hp_ = 100 + 10 * level_;

        status_text_.setString("Level up!");
        Assets::sounds["level-up"]->play();
        status_text_.setFillColor(sf::Color::Green);
        elapsed_time_ = 0.0f;  // Resets the timer
    }
}

void Player::DrawStatus(sf::RenderTarget& target) {
    sf::Vector2f text_position = GetPosition();
    text_position.y -= 30;
    text_position.x -= 20;
    status_text_.setPosition(text_position);

    float dt = clock_.restart().asSeconds();
    elapsed_time_ += dt;

    if (elapsed_time_ <= 2.0f) {  // returns the HP text to white after 0.5 seconds
        target.draw(status_text_);
    }
}

// returns cooldown progress
float Player::CooldownProgress() const {
    if (turn_count_ >= cooldown_period_)
        return 1.0f;
    else
        return turn_count_ * 1.0f / cooldown_period_;
}

float Player::LevelProgress() const {
    return (xp_ - (level_ * 200.0f)) / 200;
}

// attacks every monster within 5 tiles
int Player::RangedAttack() {
    int earnedXP = 0;
    for (auto it = EntityManager::begin(); it != EntityManager::end(); ++it) {
        std::shared_ptr<Entity> e = *it;
        if (e->IsMonster() && DistanceBetween(this->GetPosition(), e->GetPosition()) <= 4 * 128) {
            if (e->TakeDamage(20 + 5 * level_)) {
                if (e->IsBoss())
                    killed_boss_ = true;
                earnedXP += e->MaxHP();
            }
        }
    }
    return earnedXP;
}

bool Player::DrinkHealthPotion() {
    if (inv_.HealthPotionCount() >= 1) {
        inv_.AddHealthPotions(-1);
        health_points_ += 25;
        if (health_points_ > max_hp_)
            health_points_ = max_hp_;
        return true;
    }
    return false;
}

// Handles player input, returns true if the key is valid, false otherwise
bool Player::ProcessInput(sf::Keyboard::Key key, bool is_pressed) {
    std::shared_ptr<Entity> target = nullptr;
    if (key == sf::Keyboard::E && turn_count_ >= cooldown_period_) {  // 10 turn cooldown
        AddXP(RangedAttack());
        turn_count_ = 0;
        return true;
    } else if (key == sf::Keyboard::Q)
        return DrinkHealthPotion();
    else if (key == sf::Keyboard::W)
        target = MoveAlongYAxis(false);
    else if (key == sf::Keyboard::S)
        target = MoveAlongYAxis(true);
    else if (key == sf::Keyboard::A)
        target = MoveAlongXAxis(false);
    else if (key == sf::Keyboard::D)
        target = MoveAlongXAxis(true);
    else
        return false;

    // if a monster is blocking the movement, then the player will attack that monster
    if (target) {
        if (target->IsMonster()) {
            bool died = Attack(target);
            if (target->IsBoss() && died) {
                killed_boss_ = true;
            }
            if (died) {
                AddXP(target->MaxHP());
            }
        }
    }
    turn_count_++;
    return true;
}

bool Player::CheckCollision(int (&level)[120], int& curr_level) {
    if (level[pos_] == 1) {
        inv_.AddHealthPotions(1);
        Assets::sounds["collect"]->play();
        level[pos_] = 0;
    } else if (level[pos_] == 2) {
        inv_.AddWeaponDamage(5);
        weapon_damage_ = inv_.GetWeaponDamage();
        Assets::sounds["chest-open"]->play();
        level[pos_] = 0;
    } else if (level[pos_] == 3) {  // checks that the player on a door tile
        if (pos_ == 59) {           // the player on the door leading to the room to the right
            curr_level++;
            pos_ = 3 * Constants::kTilesWidth + 1;  // entrance position
            sprite_.setPosition(128 * (pos_ % Constants::kTilesWidth), 128 * (pos_ / Constants::kTilesWidth));
        } else if (pos_ == 45) {  // the player on the door leading to the room to the left
            curr_level--;
            pos_ = 59;  // entrance position on the right side
            sprite_.setPosition(128 * (pos_ % Constants::kTilesWidth), 128 * (pos_ / Constants::kTilesWidth));
        } else if (pos_ == 112) {  // the player on the door leading to the room to the dottom
            curr_level = curr_level + 3;
            pos_ = 7;  // entrance position on the right side
            sprite_.setPosition(128 * (pos_ % Constants::kTilesWidth), 128 * (pos_ / Constants::kTilesWidth));
        } else if (pos_ == 7) {  // the player on the door leading to the room to the dottom
            curr_level = curr_level - 3;
            pos_ = 113;  // entrance position on the right side
            sprite_.setPosition(128 * (pos_ % Constants::kTilesWidth), 128 * (pos_ / Constants::kTilesWidth));
        }
        return true;
    }

    return false;
}

void Player::draw(sf::RenderTarget& target) {
    DrawStatus(target);
    target.draw(inv_);
}