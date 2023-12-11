#ifndef POTION_HPP_
#define POTION_HPP_
#include "Item.hpp"

/*! \brief Potion class, inherits from Item. 

A class inheriting from the Item class, that stores the information about the number of 
potions and healing amount of this Potion object.
*/
class Potion : public Item {
   public:
    /*! A constructor that based on slot and texture_name creates the Item object and 
    additionally takes in amount as parameter which corresponds to the amount of potions 
    stored by this Potion object. */
    Potion(int slot, const std::string& texture_name, int healingAmount, int amount)
        : Item(slot, texture_name), healingAmount_(healingAmount), amount_(amount) {
        text_.setString(std::to_string(amount_));
    }
    /*! a method inherited from the Item abstract class, that implements the 
    functionality to update the text_ of this Item object. */
    virtual void Update() {
        text_.setString(std::to_string(amount_));
    }
    /*! get amount of the potions stored by this Potion object. */
    int GetAmount() {
        return amount_;
    }
    /*! add amount of the potions stored by this Potion object. */
    void AddAmount(int amount) {
        amount_ += amount;
    }

   private:
    int amount_;    /*!< amount of potions */
    int healingAmount_;     /*!< amount of healing that this Potion object gives to the Player. */
};

#endif  // POTION_HPP_