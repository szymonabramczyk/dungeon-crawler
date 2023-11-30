#ifndef TILEMAP_HPP_
#define TILEMAP_HPP_

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    
    bool load(const std::string& tileset, sf::Vector2u tile_size, const int* tiles, unsigned int width, unsigned int height);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray vertices_;
    sf::Texture tileset_;
};
#endif