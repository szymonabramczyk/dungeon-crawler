#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_
#include <SFML/Graphics.hpp>
#include <filesystem>

#include "Item.hpp"
#include "Potion.hpp"
#include "Weapon.hpp"

/*! \brief A class that stores different types of Items. */
class Inventory : public sf::Drawable {
   public:
    Inventory();
    /*! a getter method that returns the number of health potions */
    int HealthPotionCount();
    /*! a getter method that returns the damage dealt by the Weapon stored in the Inventory. */
    int GetWeaponDamage();
    /*! a method to add the number of health potions to the Inventory. */
    void AddHealthPotions(int number);
    /*! a method to add weapon damage to the Weapon stored in the Inventory. */
    void AddWeaponDamage(int amount);
    /*! a method to update all the Items stored in the Inventory. */
    void Update();

   private:
    Potion potions_;    /*!< A Potion object that holds information about the number and healing amount of the potions stored in the Inventory. */
    Weapon weapon_;     /*!< A Weapon object that holds information about the damage dealt by the Weapon stored in the Inventory. */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;   /*!< A method to draw all the Items stored in the Inventory. */
};

#endif  // INVENTORY_HPP_