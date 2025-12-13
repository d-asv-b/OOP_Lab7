#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include "NPCFactory.hpp"
#include "Dragon.hpp"
#include "Princess.hpp"
#include "WanderingKnight.hpp"

class NPCFactoryTest : public ::testing::Test {
protected:
    NPCFactory factory;
};

// Test factory creation of Dragon
TEST_F(NPCFactoryTest, CreateDragon) {
    auto npc = factory.createNPC(NPC_Type::Dragon, 100, 200);
    EXPECT_NE(npc, nullptr);
    EXPECT_FALSE(npc->is_dead());
    auto info = npc->info();
    EXPECT_FALSE(info.empty());
}

// Test factory creation of Princess
TEST_F(NPCFactoryTest, CreatePrincess) {
    auto npc = factory.createNPC(NPC_Type::Princess, 150, 250);
    EXPECT_NE(npc, nullptr);
    EXPECT_FALSE(npc->is_dead());
    auto info = npc->info();
    EXPECT_FALSE(info.empty());
}

// Test factory creation of WanderingKnight
TEST_F(NPCFactoryTest, CreateWanderingKnight) {
    auto npc = factory.createNPC(NPC_Type::WanderingKnight, 300, 400);
    EXPECT_NE(npc, nullptr);
    EXPECT_FALSE(npc->is_dead());
    auto info = npc->info();
    EXPECT_FALSE(info.empty());
}

// Test factory creates multiple instances
TEST_F(NPCFactoryTest, CreateMultipleNPCs) {
    auto dragon = factory.createNPC(NPC_Type::Dragon, 100, 100);
    auto princess = factory.createNPC(NPC_Type::Princess, 200, 200);
    auto knight = factory.createNPC(NPC_Type::WanderingKnight, 300, 300);

    EXPECT_NE(dragon, nullptr);
    EXPECT_NE(princess, nullptr);
    EXPECT_NE(knight, nullptr);
    
    EXPECT_NE(dragon, princess);
    EXPECT_NE(dragon, knight);
    EXPECT_NE(princess, knight);
}

// Test factory with coordinates
TEST_F(NPCFactoryTest, CreateNPCWithCoordinates) {
    size_t x = 123;
    size_t y = 456;
    auto npc = factory.createNPC(NPC_Type::Dragon, x, y);
    
    EXPECT_NE(npc, nullptr);
    auto info = npc->info();
    EXPECT_FALSE(info.empty());
}

// Test factory creates independent instances
TEST_F(NPCFactoryTest, IndependentInstances) {
    auto dragon1 = factory.createNPC(NPC_Type::Dragon, 100, 100);
    auto dragon2 = factory.createNPC(NPC_Type::Dragon, 200, 200);
    
    EXPECT_NE(dragon1, dragon2);
    
    // Kill first dragon
    dragon1->kill();
    
    // Second dragon should still be alive
    EXPECT_TRUE(dragon1->is_dead());
    EXPECT_FALSE(dragon2->is_dead());
}
