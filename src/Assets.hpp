#ifndef ASSETS_HPP
#define ASSETS_HPP

#include<map>

#include "Spriteinfo.hpp"

struct Assets
{
    static void loadAssets(const std::string& path);

    static std::map <std::string, SpriteInfo> sprites; // our map that stores all sprites in game   
};

#endif // ASSETS_HPP