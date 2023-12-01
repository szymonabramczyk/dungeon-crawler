#include "Assets.hpp"

#include <filesystem>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

std::map<std::string, SpriteInfo> Assets::sprites;
std::map<std::string, sf::Font> Assets::fonts;
std::map<std::string, std::unique_ptr<sf::Sound>> Assets::sounds;
std::map<std::string, std::unique_ptr<sf::SoundBuffer>> Assets::soundBuffers;

void Assets::loadAssets(const std::string& path) {
    std::filesystem::path cwd( std::filesystem::canonical( path ) );
    std::filesystem::path file1 = cwd.parent_path().parent_path() / "player.png";
    std::filesystem::path file2 = cwd.parent_path().parent_path() / "graphics-vertex-array-tilemap-tileset.png";
    std::filesystem::path file3 = cwd.parent_path().parent_path() / "orc.png";
    std::filesystem::path file4 = cwd.parent_path().parent_path() / "Quinquefive-ALoRM.ttf";
    std::filesystem::path file5 = cwd.parent_path().parent_path() / "health-potion.png";
    std::filesystem::path file6 = cwd.parent_path().parent_path() / "orc-boss.png";
    std::filesystem::path file7 = cwd.parent_path().parent_path() / "undead.png";
    std::filesystem::path file8 = cwd.parent_path().parent_path() / "attack.wav";
    sprites["player"] = SpriteInfo(file1);
    sprites["tilemap"] = SpriteInfo(file2);
    sprites["orc"] = SpriteInfo(file3);
    sprites["health-potion"] = SpriteInfo(file5);
    sprites["orc-boss"] = SpriteInfo(file6);
    sprites["undead"] = SpriteInfo(file7);
    fonts["Quinquefive-ALoRM"].loadFromFile(file4);
    
    std::unique_ptr<sf::SoundBuffer> buffer(new sf::SoundBuffer());
    if (!buffer->loadFromFile(file8))
        throw std::runtime_error("Couldn't load sound file!");

    std::unique_ptr<sf::Sound> sound(new sf::Sound()); 
    sound->setBuffer(*buffer);

    soundBuffers.insert(std::make_pair("attack", std::move(buffer)));
    sounds.insert(std::make_pair("attack", std::move(sound)));

} 