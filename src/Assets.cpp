#include "Assets.hpp"

#include <filesystem>
#include <iostream>

#include <SFML/Graphics.hpp>

std::map<std::string, SpriteInfo> Assets::sprites;

void Assets::loadAssets(const std::string& path) {
    std::filesystem::path cwd( std::filesystem::canonical( path ) );
    std::filesystem::path file1 = cwd.parent_path().parent_path() / "player.png";
    std::filesystem::path file2 = cwd.parent_path().parent_path() / "graphics-vertex-array-tilemap-tileset.png";
    std::filesystem::path file3 = cwd.parent_path().parent_path() / "orc.png";
    std::filesystem::path file4 = cwd.parent_path().parent_path() / "Quinquefive-ALoRM.ttf";
    std::filesystem::path file5 = cwd.parent_path().parent_path() / "health-potion.png";
    std::filesystem::path file6 = cwd.parent_path().parent_path() / "orc-boss.png";
    std::filesystem::path file7 = cwd.parent_path().parent_path() / "undead.png";
    sprites["player"] = SpriteInfo(file1);
    sprites["tilemap"] = SpriteInfo(file2);
    sprites["orc"] = SpriteInfo(file3);
    sprites["health-potion"] = SpriteInfo(file5);
    sprites["orc-boss"] = SpriteInfo(file6);
    sprites["undead"] = SpriteInfo(file7);
    fonts["Quinquefive-ALoRM"].loadFromFile(file4);
} 

std::map<std::string, sf::Font> Assets::fonts;