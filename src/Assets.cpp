#include "Assets.hpp"

std::map<std::string, SpriteInfo> Assets::sprites;

void Assets::loadAssets()
{
    sprites["player"] = SpriteInfo("/home/viktor/dungeon_crawler/dungeon-crawler-quang-ngo-01/content/sprites/player.png");
}