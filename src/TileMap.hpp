#ifndef TILEMAP_HPP_
#define TILEMAP_HPP_

#include <SFML/Graphics.hpp>

/*! \brief A class that is responsible for displaying the levels in form of tiles. */
class TileMap : public sf::Drawable, public sf::Transformable {
   public:
    /*! A method that loads the level based on the tiles parameter, which represents 
    the level, width and height represent the dimensions in tiles of the level, tile_size 
    represents the size of each tile in pixels and tileset_name is the name of the tile 
    set stored in the Assets texture map. */
    bool Load(const std::string& tileset_name, sf::Vector2u tile_size, const int* tiles, unsigned int width, unsigned int height);

   private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray vertices_;
    std::string tileset_name_;
};
#endif  // TILEMAP_HPP_