#include <gtest/gtest.h>

#include "../src/Entity.hpp"

class EntityTest : public ::testing::Test {
   protected:
    std::shared_ptr<Entity> entity;

    void SetUp() override {
        entity = std::make_shared<Entity>("TestType", 100);
    }

    void TearDown() override {
    }
};

// Test for Entity construction
TEST_F(EntityTest, Constructor) {
    EXPECT_EQ(entity->GetType(), "TestType");
    EXPECT_EQ(entity->GetHitPoints(), 100);
}
