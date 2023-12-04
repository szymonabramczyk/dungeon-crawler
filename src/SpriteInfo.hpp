#ifndef SPRITEINFO_HPP
#define SPRITEINFO_HPP

#include <iostream>

#include <SFML/Graphics.hpp>

struct SpriteInfo // structers that stores assets info - texture size and hitbox
{
    SpriteInfo() {}
    SpriteInfo(std::string path, int frames=1, int framesPerRow=1) :
        mFrames(frames),
        mFramesPerRow(framesPerRow)
    {   
        if (!mTexture.loadFromFile(path))
            throw std::runtime_error("Couldn't load sprite file: " + path);
        mFrameDim = sf::Vector2f(mTexture.getSize().x/mFramesPerRow, mTexture.getSize().y/(mFrames/mFramesPerRow));
        mHitBox = sf::FloatRect(0.f, 0.f, mFrameDim.x, mFrameDim.y);
    }

    sf::Texture mTexture;
    int mFrames;
    int mFramesPerRow;
    sf::Vector2f mFrameDim;
    sf::FloatRect mHitBox;
};

#endif 