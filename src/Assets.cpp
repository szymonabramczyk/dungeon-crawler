#include "Assets.hpp"

std::map<std::string, SpriteInfo> Assets::sprites;

void Assets::loadAssets()
{
    // sprites["player"] = SpriteInfo("../content/sprites/player.png");
    sprites["player"] = SpriteInfo("player.png");
}