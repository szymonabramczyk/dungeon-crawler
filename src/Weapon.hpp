#ifndef WEAPON_HPP_
#define WEAPON_HPP_
#include "Item.hpp"

class Weapon : public Item {
   public:
    Weapon(int slot, const std::string& texture_name, int damage)
        : Item(slot, texture_name), damage_(damage) {
        text_.setString(std::to_string(damage_));
    }
    // A method to Update, updates the text displaying the damage
    virtual void Update() {
        text_.setString(std::to_string(damage_));
    }
    void AddDamage(int amount) {
        damage_ += amount;
    }
    int GetDamage() {
        return damage_;
    }

   private:
    int damage_;
};

#endif  // WEAPON_HPP_