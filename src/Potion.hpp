#ifndef POTION_HPP_
#define POTION_HPP_
#include "Item.hpp"

/*! \brief Potion class, inherits from Item. */
class Potion : public Item {
   public:
    Potion(int slot, const std::string& texture_name, int healingAmount, int amount)
        : Item(slot, texture_name), healingAmount_(healingAmount), amount_(amount) {
        text_.setString(std::to_string(amount_));
    }
    // A method to Update, updates the displayed text with amount
    virtual void Update() {
        text_.setString(std::to_string(amount_));
    }
    int GetAmount() {
        return amount_;
    }
    void AddAmount(int amount) {
        amount_ += amount;
    }

   private:
    int amount_;
    int healingAmount_;
};

#endif  // POTION_HPP_