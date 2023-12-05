#include "Item.hpp"
#include "Assets.hpp"

#include <iostream>

Item::Item(int amount, int slot, const std::string& texture_name) : amount_(amount), slot_(slot) {
    text_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    text_.setCharacterSize(28);
    text_.setFillColor(sf::Color::White);
    text_.setPosition(sf::Vector2f(slot*100 + 40, 830));
    text_.setString(std::to_string(amount_));
    sprite_ = sf::Sprite(*Assets::textures[texture_name]);
    sprite_.setPosition(sf::Vector2f(slot*128 + 40, 790));
}

void Item::update() {
    text_.setString(std::to_string(amount_));
}

void Item::addAmount(int amount) {
    amount_ += amount;
}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(text_);
    target.draw(sprite_);
}