#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <SFML/Graphics.hpp>

/*! \brief Abstract class for items. 

An abstract class providing basic functionality for Items, along with basic methods 
allowing to display it properly on the screen according to the slot.
*/
class Item {
   public:
    /*! A constructor that as parameters takes in a slot that the item will 
    be displayed at (indexed from 0) and the texture_name that will be displayed 
    for the item. */
    Item(int slot, const std::string& texture_name);
    /*! A method to draw the Item to the target (screen). Draws the text_ and 
    the sprite_ associated with the Item. */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    /*! An abstract method to update the status of the Item. For the classes 
    inheriting from Item class it is updating the displayed text_, but could be 
    extended to other functionality. */
    virtual void Update() = 0;

   protected:
    int slot_;      /*!< slot number that the Item should be displayed at */
    sf::Font font_;     /*!< font used to display the text associated with the Item. */
    sf::Text text_;     /*!< text that is displayed with the Item, describing some property of the Item like amount or damage. */
    sf::Sprite sprite_;     /*!< sprite that is displayed with the Item. */
};

#endif  // ITEM_HPP