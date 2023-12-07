#include <gtest/gtest.h>
#include <filesystem>
#include "../src/Weapon.hpp"
#include "../src/Assets.hpp"

extern std::filesystem::path buildPath;

class WeaponTest : public ::testing::Test {
    protected:
        Weapon* weapon;
        void SetUp() override {
            Assets::loadTexture("sword", buildPath / "sword.png" );
            weapon = new Weapon(1, "sword", 10);
        }
        void TearDown() override {
            delete weapon;
        }
};

TEST_F(WeaponTest, Constructor) {
    EXPECT_TRUE(weapon->getDamage() == 10);
}

TEST_F(WeaponTest, AddDamage) {
    weapon->addDamage(5);
    EXPECT_EQ(weapon->getDamage(), 15);
}
