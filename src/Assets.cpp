#include "Assets.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <map>

std::map<std::string, std::unique_ptr<sf::Texture>> Assets::textures;
std::map<std::string, std::unique_ptr<sf::Font>> Assets::fonts;
std::map<std::string, std::unique_ptr<sf::Sound>> Assets::sounds;
std::map<std::string, std::unique_ptr<sf::SoundBuffer>> Assets::sound_buffers_;

void Assets::LoadAssets(const std::string& path,
                        const std::vector<std::string>& texture_names,
                        const std::vector<std::string>& font_names,
                        const std::vector<std::string>& sound_names) {
    std::filesystem::path cwd(std::filesystem::canonical(path));
    cwd = cwd.parent_path().parent_path();

    // a loop to automatically load textures with given names into the textures map
    for (const auto& texture_name : texture_names) {
        std::filesystem::path file = cwd / texture_name;
        std::string::size_type pos = texture_name.find('.');
        if (pos != std::string::npos) {
            std::string tmp = texture_name.substr(0, pos);
            LoadTexture(tmp, file);
        }
    }
    // a loop to automatically load fonts with given names into the fonts map
    for (const auto& font_name : font_names) {
        std::filesystem::path file = cwd / font_name;
        std::string::size_type pos = font_name.find('.');
        if (pos != std::string::npos) {
            std::string tmp = font_name.substr(0, pos);
            LoadFont(tmp, file);
        }
    }
    // a loop to automatically load sounds with given names into the sounds map
    for (const auto& sound_name : sound_names) {
        std::filesystem::path file = cwd / sound_name;
        std::string::size_type pos = sound_name.find('.');
        if (pos != std::string::npos) {
            std::string tmp = sound_name.substr(0, pos);
            LoadSound(tmp, file);
        }
    }
}

// a method to load sprite with a given name and a path
void Assets::LoadTexture(const std::string& name, const std::string& file_path) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture);
    if (!texture->loadFromFile(file_path))
        throw std::runtime_error("Couldn't load " + name + " texture file: " + file_path);
    textures.insert(std::make_pair(name, std::move(texture)));
}

// a method to load font with a given name and a path
void Assets::LoadFont(const std::string& name, const std::string& file_path) {
    std::unique_ptr<sf::Font> font(new sf::Font());
    if (!font->loadFromFile(file_path))
        throw std::runtime_error("Couldn't load " + name + " font file: " + file_path);
    fonts.insert(std::make_pair(name, std::move(font)));
}

// a method to load sound with a given name and a path
void Assets::LoadSound(const std::string& name, const std::string& file_path) {
    std::unique_ptr<sf::SoundBuffer> buffer(new sf::SoundBuffer());
    if (!buffer->loadFromFile(file_path))
        throw std::runtime_error("Couldn't load " + name + " sound file: " + file_path);

    std::unique_ptr<sf::Sound> sound(new sf::Sound());
    sound->setBuffer(*buffer);

    sound_buffers_.insert(std::make_pair(name, std::move(buffer)));
    sounds.insert(std::make_pair(name, std::move(sound)));
}