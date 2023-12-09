#include <gtest/gtest.h>

#include "../src/Entity.hpp"
#include "../src/EntityManager.hpp"

class EntityManagerTest : public ::testing::Test {
   protected:
    void SetUp() override {
        EntityManager::ClearEntities();  // Ensure a clean state before each test
    }

    void TearDown() override {
        EntityManager::ClearEntities();  // Clean up after each test
    }
};

// Test for adding an entity
TEST_F(EntityManagerTest, AddEntity) {
    auto entity = std::make_shared<Entity>("TestType", 100);
    EntityManager::AddEntity(entity);

    auto it = EntityManager::begin();
    bool isNotEmpty = it != EntityManager::end();
    auto firstEntity = isNotEmpty ? *it : nullptr;

    EXPECT_TRUE(isNotEmpty);
    EXPECT_EQ(firstEntity, entity);
}

// Test for removing an entity
TEST_F(EntityManagerTest, RemoveEntity) {
    auto entity = std::make_shared<Entity>("TestType", 100);
    EntityManager::AddEntity(entity);
    EntityManager::RemoveEntity(entity);

    EXPECT_EQ(EntityManager::begin(), EntityManager::end());
}

// Test for removing the dead entities
TEST_F(EntityManagerTest, RemoveDead) {
    auto entity1 = std::make_shared<Entity>("TestType1", 100);
    auto entity2 = std::make_shared<Entity>("TestType2", 0);  // Set HP to 0 to simulate dead entity
    auto entity3 = std::make_shared<Entity>("TestType3", 100);

    EntityManager::AddEntity(entity1);
    EntityManager::AddEntity(entity2);
    EntityManager::AddEntity(entity3);

    EntityManager::RemoveDead();

    int count = std::distance(EntityManager::begin(), EntityManager::end());
    EXPECT_EQ(count, 3);
}

// Test for removing all entities
TEST_F(EntityManagerTest, ClearEntities) {
    auto entity1 = std::make_shared<Entity>("TestType1", 100);
    auto entity2 = std::make_shared<Entity>("TestType2", 100);
    EntityManager::AddEntity(entity1);
    EntityManager::AddEntity(entity2);

    EntityManager::ClearEntities();

    EXPECT_EQ(EntityManager::begin(), EntityManager::end());
}