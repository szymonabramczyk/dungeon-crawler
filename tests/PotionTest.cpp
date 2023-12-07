#include <gtest/gtest.h>
#include <filesystem>
#include "../src/Potion.hpp"
#include "../src/Assets.hpp"

extern std::filesystem::path buildPath;

class PotionTest : public ::testing::Test {
    protected:
        Potion* potion;
        void SetUp() override {
            Assets::loadTexture("health-potion", buildPath / "health-potion.png" );
            potion = new Potion(1, "health-potion", 1, 10);
        }
        void TearDown() override {
            delete potion;
        }
};

TEST_F(PotionTest, Constructor) {
    EXPECT_TRUE(potion->getAmount() == 10);
}

TEST_F(PotionTest, AddDamage) {
    potion->addAmount(5);
    EXPECT_EQ(potion->getAmount(), 15);
}
