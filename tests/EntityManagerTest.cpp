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
    auto entities = EntityManager::GetEntities();
    EXPECT_EQ(entities.size(), 1);
    EXPECT_EQ(entities.front(), entity);
}

// Test for removing an entity
TEST_F(EntityManagerTest, RemoveEntity) {
    auto entity = std::make_shared<Entity>("TestType", 100);
    EntityManager::AddEntity(entity);
    EntityManager::RemoveEntity(entity);
    auto entities = EntityManager::GetEntities();
    EXPECT_TRUE(entities.empty());
}

// Test for removing the dead entities
TEST_F(EntityManagerTest, RemoveDead) {
    auto entity1 = std::make_shared<Entity>("TestType1", 100);
    auto entity2 = std::make_shared<Entity>("TestType2", 100);
    auto entity3 = std::make_shared<Entity>("TestType3", 100);
    EntityManager::AddEntity(entity1);
    EntityManager::AddEntity(entity2);
    EntityManager::AddEntity(entity3);
    auto entities = EntityManager::GetEntities();
    EXPECT_EQ(entities.size(), 3);
    EntityManager::RemoveDead();
    EXPECT_EQ(entities.size(), 3);
}

// Test for removing all entities
TEST_F(EntityManagerTest, ClearEntities) {
    auto entity1 = std::make_shared<Entity>("TestType1", 100);
    auto entity2 = std::make_shared<Entity>("TestType2", 100);
    EntityManager::AddEntity(entity1);
    EntityManager::AddEntity(entity2);
    auto entities = EntityManager::GetEntities();
    EXPECT_EQ(entities.size(), 2);
    EntityManager::ClearEntities();
    entities = EntityManager::GetEntities();
    EXPECT_TRUE(entities.empty());
}