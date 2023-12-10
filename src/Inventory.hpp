#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_
#include <SFML/Graphics.hpp>
#include <filesystem>

#include "Item.hpp"
#include "Potion.hpp"
#include "Weapon.hpp"

/*! \brief Represents the player's inventory. */
class Inventory : public sf::Drawable {
   public:
    Inventory();
    int HealthPotionCount();
    int GetWeaponDamage();
    void AddHealthPotions(int number);
    void AddWeaponDamage(int amount);
    void Update();

   private:
    Potion potions_;
    Weapon weapon_;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif  // INVENTORY_HPP_