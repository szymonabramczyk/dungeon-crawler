#include "Inventory.hpp"
#include "Assets.hpp"

#include <iostream>

Inventory::Inventory() : health_potions_(0) {
    health_potions_text_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    health_potions_text_.setCharacterSize(28);
    health_potions_text_.setFillColor(sf::Color::White);
    health_potions_text_.setPosition(sf::Vector2f(40, 830));
    health_potions_text_.setString(std::to_string(health_potions_));
    health_potions_sprite_ = sf::Sprite(*Assets::textures["health-potion"]);
    health_potions_sprite_.setPosition(sf::Vector2f(40, 790));
}

int Inventory::healthPotionCount() { return health_potions_; }

// A method to change the number of potions owned by the player
void Inventory::addHealthPotions(int number) {
    health_potions_ += number;
    update();
}

// A method to update (the texts content)
void Inventory::update() {
    health_potions_text_.setString(std::to_string(health_potions_));
}

// A method to draw the Inventory to the screen
void Inventory::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(health_potions_text_);
    target.draw(health_potions_sprite_);
}