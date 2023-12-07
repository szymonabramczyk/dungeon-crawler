#include <gtest/gtest.h>
#include <filesystem>
#include "../src/Inventory.hpp"
#include "../src/Assets.hpp"

extern std::filesystem::path buildPath;

class InventoryTest : public ::testing::Test {
    protected:
        Inventory* inventory;
        void SetUp() override {
            Assets::loadTexture("health-potion", buildPath / "health-potion.png" );
            Assets::loadTexture("sword", buildPath / "sword.png" );
            inventory = new Inventory();
        }
        void TearDown() override {
            delete inventory;
        }
};

TEST_F(InventoryTest, HealthPotionCount) {
    EXPECT_EQ(inventory->healthPotionCount(), 0);
}

TEST_F(InventoryTest, GetWeaponDamage) {
    EXPECT_GE(inventory->getWeaponDamage(), 0);
}

TEST_F(InventoryTest, AddHealthPotions) {
    inventory->addHealthPotions(5);
    EXPECT_EQ(inventory->healthPotionCount(), 5);
}

TEST_F(InventoryTest, AddWeaponDamage) {
    int tmp = inventory->getWeaponDamage();
    inventory->addWeaponDamage(10);
    EXPECT_EQ(inventory->getWeaponDamage(), tmp + 10);
}