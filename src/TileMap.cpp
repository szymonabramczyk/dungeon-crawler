#include "TileMap.hpp"

#include <SFML/Graphics.hpp>

#include "Assets.hpp"

bool TileMap::Load(const std::string& tileset_name, sf::Vector2u tile_size, const int* tiles, unsigned int width, unsigned int height) {
    tileset_name_ = tileset_name;
    // resize the vertex array to fit the level size
    vertices_.setPrimitiveType(sf::Quads);
    vertices_.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; i++)
        for (unsigned int j = 0; j < height; j++) {
            // get the current tile number
            int tileNumber = tiles[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % ((*Assets::textures[tileset_name_]).getSize().x / tile_size.x);
            int tv = tileNumber / ((*Assets::textures[tileset_name_]).getSize().x / tile_size.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &vertices_[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tile_size.x, j * tile_size.y);
            quad[1].position = sf::Vector2f((i + 1) * tile_size.x, j * tile_size.y);
            quad[2].position = sf::Vector2f((i + 1) * tile_size.x, (j + 1) * tile_size.y);
            quad[3].position = sf::Vector2f(i * tile_size.x, (j + 1) * tile_size.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
            quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
        }

    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = Assets::textures[tileset_name_].get();

    // draw the vertex array
    target.draw(vertices_, states);
}
