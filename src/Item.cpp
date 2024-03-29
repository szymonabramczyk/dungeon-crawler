#include "Item.hpp"

#include <iostream>

#include "Assets.hpp"

Item::Item(int slot, const std::string& texture_name) : slot_(slot) {
    text_.setFont(*Assets::fonts["Quinquefive-ALoRM"]);
    text_.setCharacterSize(28);
    text_.setFillColor(sf::Color::White);
    text_.setPosition(sf::Vector2f(slot * 100 + 40, 830));
    sprite_ = sf::Sprite(*Assets::textures[texture_name]);
    sprite_.setPosition(sf::Vector2f(slot * 128 + 40, 790));
}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(text_);
    target.draw(sprite_);
}