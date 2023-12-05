#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_
#include "Item.hpp"
#include "Weapon.hpp"
#include "Potion.hpp"

#include <filesystem>

#include <SFML/Graphics.hpp>

class Inventory : public sf::Drawable {
    public:
        Inventory();
        int healthPotionCount();
        int getWeaponDamage();
        void addHealthPotions(int number);
        void addWeaponDamage(int amount);
        void update();
        
    private:
        Potion potions_;
        Weapon weapon_;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // INVENTORY_HPP_