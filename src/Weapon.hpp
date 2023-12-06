#ifndef WEAPON_HPP_
#define WEAPON_HPP_
#include "Item.hpp"

class Weapon : public Item {
    public:
        Weapon(int amount, int slot, const std::string& texture_name, int damage) 
            : Item(amount, slot, texture_name), damage_(damage) {
            text_.setString(std::to_string(damage_));
        }
        void update() {
            text_.setString(std::to_string(damage_));
        }
        void addDamage(int amount) {
            damage_ += amount;
        }
        
        int getDamage() {
            return damage_;
        }
    private:
        int damage_;
};

#endif // WEAPON_HPP_