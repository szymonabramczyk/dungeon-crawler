#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <SFML/Graphics.hpp>

class Item {
    public:
        Item(int amount, int slot, const std::string& texture_name);
        void addAmount(int amount);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void update();
        int getAmount() {
            return amount_;
        }
    
    protected:
        int amount_;
        int slot_;
        sf::Font font_;
        sf::Text text_;
        sf::Sprite sprite_;
};

#endif // ITEM_HPP