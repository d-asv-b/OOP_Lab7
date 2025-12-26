#include <gtest/gtest.h>
#include <memory>
#include <thread>
#include "../include/application/FightManager.hpp"
#include "../include/npc/Dragon.hpp"

class FightManagerTest : public ::testing::Test {
protected:
    FightManager& fightManager = FightManager::get();
    std::shared_ptr<Dragon> dragon1;
    std::shared_ptr<Dragon> dragon2;

    void SetUp() override {
        dragon1 = std::make_shared<Dragon>(100, 200);
        dragon2 = std::make_shared<Dragon>(130, 230);
    }

    void TearDown() override {
        // Clear any remaining events
        while (fightManager.has_events()) {
            fightManager.get_event();
        }
    }
};

// Test FightManager singleton
TEST_F(FightManagerTest, SingletonInstance) {
    FightManager& instance1 = FightManager::get();
    FightManager& instance2 = FightManager::get();
    EXPECT_EQ(&instance1, &instance2);
}

// Test adding and getting events
TEST_F(FightManagerTest, AddAndGetEvent) {
    EXPECT_FALSE(fightManager.has_events());

    FightEvent event{dragon1, dragon2};
    fightManager.add_event(event);

    EXPECT_TRUE(fightManager.has_events());

    FightEvent retrieved = fightManager.get_event();
    EXPECT_EQ(retrieved.attacker, dragon1);
    EXPECT_EQ(retrieved.defender, dragon2);

    EXPECT_FALSE(fightManager.has_events());
}

// Test multiple events
TEST_F(FightManagerTest, MultipleEvents) {
    auto dragon3 = std::make_shared<Dragon>(300, 400);
    auto dragon4 = std::make_shared<Dragon>(330, 430);

    FightEvent event1{dragon1, dragon2};
    FightEvent event2{dragon3, dragon4};
    FightEvent event3{dragon2, dragon3};

    fightManager.add_event(event1);
    fightManager.add_event(event2);
    fightManager.add_event(event3);

    EXPECT_TRUE(fightManager.has_events());
    EXPECT_EQ(fightManager.get_event().attacker, dragon1);
    EXPECT_EQ(fightManager.get_event().attacker, dragon3);
    EXPECT_EQ(fightManager.get_event().attacker, dragon2);

    EXPECT_FALSE(fightManager.has_events());
}

// Test FIFO order
TEST_F(FightManagerTest, FIFOOrder) {
    auto dragon3 = std::make_shared<Dragon>(300, 400);

    FightEvent event1{dragon1, dragon2};
    FightEvent event2{dragon2, dragon3};

    fightManager.add_event(event1);
    fightManager.add_event(event2);

    FightEvent first = fightManager.get_event();
    EXPECT_EQ(first.attacker, dragon1);
    EXPECT_EQ(first.defender, dragon2);

    FightEvent second = fightManager.get_event();
    EXPECT_EQ(second.attacker, dragon2);
    EXPECT_EQ(second.defender, dragon3);
}

// Test thread safety - basic test
TEST_F(FightManagerTest, ThreadSafety) {
    auto dragon3 = std::make_shared<Dragon>(300, 400);
    auto dragon4 = std::make_shared<Dragon>(330, 430);

    std::thread producer1([&]() {
        for (int i = 0; i < 10; ++i) {
            FightEvent event{dragon1, dragon2};
            fightManager.add_event(event);
        }
    });

    std::thread producer2([&]() {
        for (int i = 0; i < 10; ++i) {
            FightEvent event{dragon3, dragon4};
            fightManager.add_event(event);
        }
    });

    producer1.join();
    producer2.join();

    // Should have 20 events
    int eventCount = 0;
    while (fightManager.has_events()) {
        fightManager.get_event();
        ++eventCount;
    }

    EXPECT_EQ(eventCount, 20);
}

// Test empty queue behavior
TEST_F(FightManagerTest, EmptyQueue) {
    EXPECT_FALSE(fightManager.has_events());

    // Getting from empty queue should not crash, but we can't test the actual behavior
    // without modifying FightManager to handle empty queue gracefully
    // For now, just ensure has_events returns false
}

// Test event structure
TEST_F(FightManagerTest, EventStructure) {
    FightEvent event{dragon1, dragon2};

    EXPECT_EQ(event.attacker, dragon1);
    EXPECT_EQ(event.defender, dragon2);
    EXPECT_NE(event.attacker, event.defender);
}

// Test null pointers in events
TEST_F(FightManagerTest, NullPointerEvents) {
    FightEvent event{nullptr, dragon2};
    fightManager.add_event(event);

    EXPECT_TRUE(fightManager.has_events());
    FightEvent retrieved = fightManager.get_event();
    EXPECT_EQ(retrieved.attacker, nullptr);
    EXPECT_EQ(retrieved.defender, dragon2);
}

// Test same attacker and defender
TEST_F(FightManagerTest, SameAttackerDefender) {
    FightEvent event{dragon1, dragon1};
    fightManager.add_event(event);

    FightEvent retrieved = fightManager.get_event();
    EXPECT_EQ(retrieved.attacker, dragon1);
    EXPECT_EQ(retrieved.defender, dragon1);
}
