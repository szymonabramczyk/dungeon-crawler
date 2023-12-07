#include <gtest/gtest.h>
#include <filesystem>
#include "../src/Potion.hpp"
#include "../src/Assets.hpp"

extern std::filesystem::path build_path;

class PotionTest : public ::testing::Test {
    protected:
        Potion* potion;
        void SetUp() override {
            Assets::LoadTexture("health-potion", build_path / "health-potion.png" );
            potion = new Potion(1, "health-potion", 1, 10);
        }
        void TearDown() override {
            delete potion;
        }
};

TEST_F(PotionTest, Constructor) {
    EXPECT_TRUE(potion->GetAmount() == 10);
}

TEST_F(PotionTest, AddDamage) {
    potion->AddAmount(5);
    EXPECT_EQ(potion->GetAmount(), 15);
}
