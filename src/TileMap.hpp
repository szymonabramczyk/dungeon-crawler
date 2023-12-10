#ifndef TILEMAP_HPP_
#define TILEMAP_HPP_

#include <SFML/Graphics.hpp>

/*! \brief Class for loading and drawing the tilemap. */
class TileMap : public sf::Drawable, public sf::Transformable {
   public:
    bool Load(const std::string& tileset_name, sf::Vector2u tile_size, const int* tiles, unsigned int width, unsigned int height);

   private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray vertices_;
    std::string tileset_name_;
};
#endif  // TILEMAP_HPP_