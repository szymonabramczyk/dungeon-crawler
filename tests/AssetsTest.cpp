#include <gtest/gtest.h>

#include <filesystem>

#include "../src/Assets.hpp"

extern std::filesystem::path build_path;
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
    Assets::LoadTexture("player", build_path / "player.png");
    EXPECT_TRUE(Assets::textures["player"] != NULL);
}

// Test for unsuccessful sprite loading
TEST(AssetsTest, LoadSpriteFailure) {
    EXPECT_THROW(Assets::LoadTexture("invalidSprite", "path/to/nonexistent.png"), std::runtime_error);
}

// Test for successful font loading
TEST(AssetsTest, LoadFontSuccess) {
    Assets::LoadFont("Quinquefive-ALoRM", build_path / "Quinquefive-ALoRM.ttf");
    EXPECT_TRUE(Assets::fonts["Quinquefive-ALoRM"] != NULL);
}

// Test for sound loading
TEST(AssetsTest, LoadSoundSuccess) {
    Assets::LoadSound("attack", build_path / "attack.wav");
    EXPECT_TRUE(Assets::sounds["attack"] != NULL);
}