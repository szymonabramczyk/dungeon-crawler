#include "Assets.hpp"

#include <filesystem>
#include <iostream>

std::map<std::string, SpriteInfo> Assets::sprites;

void Assets::loadAssets(const std::string& path) {
    std::filesystem::path cwd( std::filesystem::canonical( path ) );
    std::filesystem::path file1 = cwd.parent_path().parent_path() / "player.png";
    std::filesystem::path file2 = cwd.parent_path().parent_path() / "graphics-vertex-array-tilemap-tileset.png";
    sprites["player"] = SpriteInfo(file1);
    sprites["tilemap"] = SpriteInfo(file2);
} 