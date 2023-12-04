#include <gtest/gtest.h>
#include <filesystem>
#include "../src/Assets.hpp"

extern std::filesystem::path buildPath;
// Test Fixture for Assets
class AssetsTest : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test for successful sprite loading
TEST_F(AssetsTest, LoadSpriteSuccess) {
    Assets::loadSprite("player", buildPath / "player.png" );
    EXPECT_TRUE(Assets::sprites["player"] != NULL);
}

// Test for unsuccessful sprite loading
TEST_F(AssetsTest, LoadSpriteFailure) {
    Assets::loadSprite("invalidSprite", "path/to/nonexistent.png");
    EXPECT_TRUE(Assets::sprites["invalidSprite"]->mTexture.getSize().x == 0 
                || Assets::sprites["invalidSprite"]->mTexture.getSize().y == 0);
}

// Test for successful font loading
TEST_F(AssetsTest, LoadFontSuccess) {
    Assets::loadFont("Quinquefive-ALoRM", buildPath / "Quinquefive-ALoRM.ttf");
    EXPECT_TRUE(Assets::fonts["Quinquefive-ALoRM"] != NULL);
}

// Test for sound loading
TEST_F(AssetsTest, LoadSoundSuccess) {
    Assets::loadSound("attack", buildPath / "attack.wav");
    EXPECT_TRUE(Assets::sounds["attack"] != NULL);
}



