#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <SFML/Graphics.hpp>

// Abstract class for Items
class Item {
    public:
        Item(int slot, const std::string& texture_name);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void update() = 0;
    
    protected:
        int slot_;
        sf::Font font_;
        sf::Text text_;
        sf::Sprite sprite_;
};

#endif // ITEM_HPP