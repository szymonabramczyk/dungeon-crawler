#include <gtest/gtest.h>
#include <filesystem>
#include "../src/Weapon.hpp"
#include "../src/Assets.hpp"

extern std::filesystem::path build_path;

class WeaponTest : public ::testing::Test {
    protected:
        Weapon* weapon;
        void SetUp() override {
            Assets::LoadTexture("sword", build_path / "sword.png" );
            weapon = new Weapon(1, "sword", 10);
        }
        void TearDown() override {
            delete weapon;
        }
};

TEST_F(WeaponTest, Constructor) {
    EXPECT_TRUE(weapon->GetDamage() == 10);
}

TEST_F(WeaponTest, AddDamage) {
    weapon->AddDamage(5);
    EXPECT_EQ(weapon->GetDamage(), 15);
}
