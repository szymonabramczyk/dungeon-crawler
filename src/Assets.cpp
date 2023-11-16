#include "Assets.hpp"

#include <filesystem>
#include <iostream>

std::map<std::string, SpriteInfo> Assets::sprites;

void Assets::loadAssets(const std::string& path) {
    std::filesystem::path cwd( std::filesystem::canonical( path ) );
    std::filesystem::path file = cwd.parent_path().parent_path() / "player.png";
    sprites["player"] = SpriteInfo(file);
} 