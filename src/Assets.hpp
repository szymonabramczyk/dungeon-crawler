#ifndef ASSETS_HPP
#define ASSETS_HPP

#include "SpriteInfo.hpp"

#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct Assets
{
    static void loadAssets(const std::string& path);
    static void loadSound(const std::string& name, const std::string& filePath);
    static void loadFont(const std::string& name, const std::string& filePath);
    static void loadSprite(const std::string& name, const std::string& filePath);

    static std::map <std::string, std::unique_ptr<SpriteInfo>> sprites; // our map that stores all sprites in game 
    static std::map <std::string, std::unique_ptr<sf::Font>> fonts;
    static std::map <std::string, std::unique_ptr<sf::Sound>> sounds;
    static std::map <std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers;
};

#endif // ASSETS_HPP