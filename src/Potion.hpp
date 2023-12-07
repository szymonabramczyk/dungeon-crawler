#ifndef POTION_HPP_
#define POTION_HPP_
#include "Item.hpp"

class Potion : public Item {
    public:
        Potion(int slot, const std::string& texture_name, int healingAmount, int amount) 
            : Item(slot, texture_name), healingAmount_(healingAmount), amount_(amount) { 
                text_.setString(std::to_string(amount_));
        }
        // A method to update, updates the displayed text with amount
        virtual void update() {
            text_.setString(std::to_string(amount_));
        }
        int getAmount() {
            return amount_;
        }
        void addAmount(int amount) {
            amount_ += amount;
        }
    private:
        int amount_;
        int healingAmount_;
};

#endif // POTION_HPP_