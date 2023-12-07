#include "Inventory.hpp"

#include <iostream>

#include "Assets.hpp"

Inventory::Inventory() : potions_(0, "health-potion", 25, 0), weapon_(1, "sword", 25) {
}

int Inventory::HealthPotionCount() {
    return potions_.GetAmount();
}

int Inventory::GetWeaponDamage() {
    return weapon_.GetDamage();
}
// A method to change the number of potions owned by the player
void Inventory::AddHealthPotions(int number) {
    potions_.AddAmount(number);
    potions_.Update();
}

// A method to Update the amount of damage dealt by the weapon
void Inventory::AddWeaponDamage(int amount) {
    weapon_.AddDamage(amount);
    weapon_.Update();
}

// A method to Update (the texts content)
void Inventory::Update() {
    potions_.Update();
    weapon_.Update();
}

// A method to draw the Inventory to the screen
void Inventory::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    potions_.draw(target, states);
    weapon_.draw(target, states);
}