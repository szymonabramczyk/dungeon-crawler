#include "Inventory.hpp"
#include "Assets.hpp"

#include <iostream>

Inventory::Inventory() : potions_(0, "health-potion", 25, 0), weapon_(1, "sword", 25) {
}

int Inventory::healthPotionCount() { 
    return potions_.getAmount(); 
}

int Inventory::getWeaponDamage() {
    return weapon_.getDamage();
}
// A method to change the number of potions owned by the player
void Inventory::addHealthPotions(int number) {
    potions_.addAmount(number);
    potions_.update();
}

// A method to update the amount of damage dealt by the weapon
void Inventory::addWeaponDamage(int amount) {
    weapon_.addDamage(amount);
    weapon_.update();
}

// A method to update (the texts content)
void Inventory::update() {
    potions_.update();
    weapon_.update();
}

// A method to draw the Inventory to the screen
void Inventory::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    potions_.draw(target, states);
    weapon_.draw(target, states);
}