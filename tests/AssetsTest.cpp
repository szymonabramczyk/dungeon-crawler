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
TEST(AssetsTest, LoadSpriteSuccess) {
    Assets::loadTexture("player", buildPath / "player.png" );
    EXPECT_TRUE(Assets::textures["player"] != NULL);
}

// Test for unsuccessful sprite loading
TEST(AssetsTest, LoadSpriteFailure) {
    EXPECT_THROW(Assets::loadTexture("invalidSprite", "path/to/nonexistent.png"), std::runtime_error);
}

// Test for successful font loading
TEST(AssetsTest, LoadFontSuccess) {
    Assets::loadFont("Quinquefive-ALoRM", buildPath / "Quinquefive-ALoRM.ttf");
    EXPECT_TRUE(Assets::fonts["Quinquefive-ALoRM"] != NULL);
}

// Test for sound loading
TEST(AssetsTest, LoadSoundSuccess) {
    Assets::loadSound("attack", buildPath / "attack.wav");
    EXPECT_TRUE(Assets::sounds["attack"] != NULL);
}