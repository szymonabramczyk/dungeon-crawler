#include "Assets.hpp"

#include <filesystem>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

std::map<std::string, std::unique_ptr<sf::Texture>> Assets::textures;
std::map<std::string, std::unique_ptr<sf::Font>> Assets::fonts;
std::map<std::string, std::unique_ptr<sf::Sound>> Assets::sounds;
std::map<std::string, std::unique_ptr<sf::SoundBuffer>> Assets::soundBuffers;


void Assets::loadAssets(const std::string& path) {
    std::string textures_names[7] = {"player.png", "tiles.png", "orc.png", "health-potion.png", "orc-boss.png", "undead.png", "sword.png"};
    std::string font_names[1] = {"Quinquefive-ALoRM.ttf"};
    std::string sounds_names[5] = {"attack.wav", "collect.wav", "chest-open.wav", "level-up.wav", "game-over.wav"};

    std::filesystem::path cwd( std::filesystem::canonical( path ) );
    cwd = cwd.parent_path().parent_path();

    // a loop to automatically load textures with given names into the textures map
    for (const auto& texture_name : textures_names) {
        std::filesystem::path file = cwd / texture_name;
        std::string::size_type pos = texture_name.find('.');
        if (pos != std::string::npos) {
            std::string tmp = texture_name.substr(0, pos);
            loadTexture(tmp, file); 
        }
    }
    // a loop to automatically load fonts with given names into the fonts map
    for (const auto& font_name : font_names) {
        std::filesystem::path file = cwd / font_name;
        std::string::size_type pos = font_name.find('.');
        if (pos != std::string::npos) {
            std::string tmp = font_name.substr(0, pos);
            loadFont(tmp, file); 
        }
    }
    // a loop to automatically load sounds with given names into the sounds map
    for (const auto& sound_name : sounds_names) {
        std::filesystem::path file = cwd / sound_name;
        std::string::size_type pos = sound_name.find('.');
        if (pos != std::string::npos) {
            std::string tmp = sound_name.substr(0, pos);
            loadSound(tmp, file); 
        }
    }
} 

// a method to load sprite with a given name and a path
void Assets::loadTexture(const std::string& name, const std::string& filePath) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture);
    if (!texture->loadFromFile(filePath))
            throw std::runtime_error("Couldn't load " + name + " texture file: " + filePath);
    textures.insert(std::make_pair(name, std::move(texture)));
}

// a method to load font with a given name and a path
void Assets::loadFont(const std::string& name, const std::string& filePath) {
    std::unique_ptr<sf::Font> font(new sf::Font());
    if (!font->loadFromFile(filePath))
        throw std::runtime_error("Couldn't load " + name + " font file: " + filePath);
    fonts.insert(std::make_pair(name, std::move(font)));
}

// a method to load sound with a given name and a path
void Assets::loadSound(const std::string& name, const std::string& filePath) {
    std::unique_ptr<sf::SoundBuffer> buffer(new sf::SoundBuffer());
    if (!buffer->loadFromFile(filePath))
        throw std::runtime_error("Couldn't load " + name + " sound file: " + filePath);

    std::unique_ptr<sf::Sound> sound(new sf::Sound()); 
    sound->setBuffer(*buffer);

    soundBuffers.insert(std::make_pair(name, std::move(buffer)));
    sounds.insert(std::make_pair(name, std::move(sound)));
}