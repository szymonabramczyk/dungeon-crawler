#ifndef POTION_HPP_
#define POTION_HPP_
#include "Item.hpp"

class Potion : public Item {
    public:
        Potion(int amount, int slot, const std::string& texture_name, int healingAmount) 
            : Item(amount, slot, texture_name), healingAmount_(healingAmount) { }
    private:
        int healingAmount_;
};

#endif // POTION_HPP_