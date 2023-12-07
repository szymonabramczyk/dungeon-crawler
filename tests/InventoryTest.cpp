#include <gtest/gtest.h>
#include <filesystem>
#include "../src/Inventory.hpp"
#include "../src/Assets.hpp"

extern std::filesystem::path build_path;

class InventoryTest : public ::testing::Test {
    protected:
        Inventory* inventory;
        void SetUp() override {
            Assets::LoadTexture("health-potion", build_path / "health-potion.png" );
            Assets::LoadTexture("sword", build_path / "sword.png" );
            inventory = new Inventory();
        }
        void TearDown() override {
            delete inventory;
        }
};

TEST_F(InventoryTest, HealthPotionCount) {
    EXPECT_EQ(inventory->HealthPotionCount(), 0);
}

TEST_F(InventoryTest, GetWeaponDamage) {
    EXPECT_GE(inventory->GetWeaponDamage(), 0);
}

TEST_F(InventoryTest, AddHealthPotions) {
    inventory->AddHealthPotions(5);
    EXPECT_EQ(inventory->HealthPotionCount(), 5);
}

TEST_F(InventoryTest, AddWeaponDamage) {
    int tmp = inventory->GetWeaponDamage();
    inventory->AddWeaponDamage(10);
    EXPECT_EQ(inventory->GetWeaponDamage(), tmp + 10);
}