#ifndef WEAPON_HPP_
#define WEAPON_HPP_
#include "Item.hpp"

/*! \brief Weapon class, inherits from Item. 

A class inheriting from the Item class, that stores the information about 
the damage the weapon of this Weapon object.
*/
class Weapon : public Item {
   public:
    /*! A constructor that based on slot and texture_name creates the Item 
    object and additionally takes in damage as parameter which corresponds 
    to the damage to be dealt by this Weapon object. */
    Weapon(int slot, const std::string& texture_name, int damage)
        : Item(slot, texture_name), damage_(damage) {
        text_.setString(std::to_string(damage_));
    }
    /*! o	a method inherited from the Item abstract class, that implements 
    the functionality to update the text_ of this Item object. */
    virtual void Update() {
        text_.setString(std::to_string(damage_));
    }
    /*! add damage to the weapon stored by this Weapon object. */
    void AddDamage(int amount) {
        damage_ += amount;
    }
    /*! get damage of the weapon stored by this Weapon object. */
    int GetDamage() {
        return damage_;
    }

   private:
    int damage_;    /*!< amount of damage that this Weapon object can deal, which is the number of health points to be decreased from enemies. */
};

#endif  // WEAPON_HPP_