#include "Inventory.hpp"
#include "Assets.hpp"

#include <iostream>

Inventory::Inventory() : health_potions_(0) {
    health_potions_text_.setFont(Assets::fonts["Arial"]);
    health_potions_text_.setCharacterSize(24);
    health_potions_text_.setFillColor(sf::Color::White);
    health_potions_text_.setPosition(sf::Vector2f(40, 980));
    health_potions_text_.setString(std::to_string(health_potions_));
}

void Inventory::addHealthPotions(int number) {
    health_potions_ += number;
    update();
}

void Inventory::update() {
    health_potions_text_.setString(std::to_string(health_potions_));
}

void Inventory::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(health_potions_text_);
}