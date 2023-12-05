#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <SFML/Graphics.hpp>

class Item {
public:
    int amount;

    Item(int amount);
    virtual void useItem();
    virtual void render(sf::RenderWindow& window, int x, int y) const;
};

class Weapon : public Item {
public:
    int damage;

    Weapon(int amount, int damage);
    void useItem() override;
    void render(sf::RenderWindow& window, int x, int y) const override;
};

class Armour : public Item {
public:
    int defense;

    Armour(int amount, int defense);
    void useItem() override;
    void render(sf::RenderWindow& window, int x, int y) const override;
};

class Potion : public Item {
public:
    int healingAmount;

    Potion(int amount, int healingAmount);
    void useItem() override;
    void render(sf::RenderWindow& window, int x, int y) const override;
};

#endif // ITEM_HPP