#include "Item.hpp"

Item::Item(int amount) : amount(amount) {}

void Item::useItem() {

}

void Item::render(sf::RenderWindow& window, int x, int y) const {
    sf::RectangleShape rect(sf::Vector2f(32, 32));
    rect.setPosition(static_cast<float>(x), static_cast<float>(y));
    rect.setFillColor(sf::Color::White);
    window.draw(rect);
}

Weapon::Weapon(int amount, int damage) : Item(amount), damage(damage) {}

void Weapon::useItem() {
    std::cout << "Attacking with " << damage << " damage." << std::endl;
}

void Weapon::render(sf::RenderWindow& window, int x, int y) const {
    sf::RectangleShape rect(sf::Vector2f(32, 32));
    rect.setPosition(static_cast<float>(x), static_cast<float>(y));
    rect.setFillColor(sf::Color::Red);
    window.draw(rect);
}

Armour::Armour(int amount, int defense) : Item(amount), defense(defense) {}

void Armour::useItem() {
    std::cout << "Equipping armor with " << defense << " defense." << std::endl;
}

void Armour::render(sf::RenderWindow& window, int x, int y) const {
    sf::RectangleShape rect(sf::Vector2f(32, 32));
    rect.setPosition(static_cast<float>(x), static_cast<float>(y));
    rect.setFillColor(sf::Color::Blue); 
    window.draw(rect);
}

Potion::Potion(int amount, int healingAmount) : Item(amount), healingAmount(healingAmount) {}

void Potion::useItem() {
    std::cout << "Using potion, healing for " << healingAmount << " health." << std::endl;
}

void Potion::render(sf::RenderWindow& window, int x, int y) const {
    sf::RectangleShape rect(sf::Vector2f(32, 32)); 
    rect.setPosition(static_cast<float>(x), static_cast<float>(y));
    rect.setFillColor(sf::Color::Green); 
    window.draw(rect);
}
