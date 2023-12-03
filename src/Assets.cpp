#include "Assets.hpp"

#include <filesystem>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

std::map<std::string, std::unique_ptr<SpriteInfo>> Assets::sprites;
std::map<std::string, std::unique_ptr<sf::Font>> Assets::fonts;
std::map<std::string, std::unique_ptr<sf::Sound>> Assets::sounds;
std::map<std::string, std::unique_ptr<sf::SoundBuffer>> Assets::soundBuffers;


void Assets::loadAssets(const std::string& path) {
    std::string sprites_names[6] = {"player.png", "tiles.png", "orc.png", "health-potion.png", "orc-boss.png", "undead.png"};

    std::filesystem::path cwd( std::filesystem::canonical( path ) );
    cwd = cwd.parent_path().parent_path();

    // a method to automatically load sprites with given names into the sprite map
    for (unsigned int i = 0; i < sprites_names->length(); i++) {
        std::filesystem::path file = cwd / sprites_names[i];
        std::string::size_type pos = sprites_names[i].find('.');
        if (pos != std::string::npos) {
            std::cout << file << std::endl;
            std::string tmp = sprites_names[i].substr(0, pos);
            loadSprite(tmp, file); 
        }
    }

    std::filesystem::path file1 = cwd / "Quinquefive-ALoRM.ttf";
    std::filesystem::path file2 = cwd / "attack.wav";
    loadFont("Quinquefive-ALoRM", file1);
    loadSound("attack", file2);
} 

// a method to load sprite with a given name and a path
void Assets::loadSprite(const std::string& name, const std::string& filePath) {
    sprites[name] = std::unique_ptr<SpriteInfo>(new SpriteInfo(filePath));
}

// a method to load font with a given name and a path
void Assets::loadFont(const std::string& name, const std::string& filePath) {
    std::unique_ptr<sf::Font> font(new sf::Font());
    font->loadFromFile(filePath);
    fonts.insert(std::make_pair(name, std::move(font)));
}

// a method to load sound with a given name and a path
void Assets::loadSound(const std::string& name, const std::string& filePath) {
    std::unique_ptr<sf::SoundBuffer> buffer(new sf::SoundBuffer());
    if (!buffer->loadFromFile(filePath))
        throw std::runtime_error("Couldn't load sound file!");

    std::unique_ptr<sf::Sound> sound(new sf::Sound()); 
    sound->setBuffer(*buffer);

    soundBuffers.insert(std::make_pair(name, std::move(buffer)));
    sounds.insert(std::make_pair(name, std::move(sound)));
}