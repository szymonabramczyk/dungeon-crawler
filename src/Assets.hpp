#ifndef ASSETS_HPP
#define ASSETS_HPP

#include "SpriteInfo.hpp"

#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct Assets
{
    static void loadAssets(const std::string& path);

    static std::map <std::string, SpriteInfo> sprites; // our map that stores all sprites in game 
    static std::map <std::string, sf::Font> fonts;
    static std::map <std::string, std::unique_ptr<sf::Sound>> sounds;
    static std::map <std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers;
};

#endif // ASSETS_HPP