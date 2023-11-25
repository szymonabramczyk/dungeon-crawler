#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <map>

#include "SpriteInfo.hpp"

struct Assets
{
    static void loadAssets(const std::string& path);

    static std::map <std::string, SpriteInfo> sprites; // our map that stores all sprites in game 
    static std::map <std::string, sf::Font> fonts;
};

#endif // ASSETS_HPP