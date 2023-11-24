#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_
#include <filesystem>

#include <SFML/Graphics.hpp>

class Inventory : public sf::Drawable {
    public:
        Inventory();
        void addHealthPotions(int number);
        void update();
        
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        int health_potions_;
        sf::Font font_;
        sf::Text health_potions_text_;
};

#endif