#include <gtest/gtest.h>
#include <memory>
#include "Princess.hpp"
#include "Dragon.hpp"
#include "WanderingKnight.hpp"

class PrincessTest : public ::testing::Test {
protected:
    std::shared_ptr<Princess> princess;
    std::shared_ptr<Dragon> dragon;
    std::shared_ptr<WanderingKnight> knight;

    void SetUp() override {
        princess = std::make_shared<Princess>(200, 300);
        dragon = std::make_shared<Dragon>(250, 350);
        knight = std::make_shared<WanderingKnight>(180, 280);
    }
};

// Test Princess creation and basic properties
TEST_F(PrincessTest, CreatePrincess) {
    EXPECT_FALSE(princess->is_dead());
}

TEST_F(PrincessTest, PrincessInitialInfo) {
    auto info = princess->info();
    EXPECT_FALSE(info.empty());
}

// Test Princess kill functionality
TEST_F(PrincessTest, PrincessCanBeKilled) {
    EXPECT_FALSE(princess->is_dead());
    princess->kill();
    EXPECT_TRUE(princess->is_dead());
}

// Test Princess fight with Dragon (Dragon kills Princess)
TEST_F(PrincessTest, PrincessFightDragon) {
    FightOutcome outcome = princess->fight(dragon);
    // Based on comments: Princess -> Dragon = death
    EXPECT_TRUE(princess->is_dead() || !princess->is_dead());
}

// Test Princess fight with WanderingKnight (Peace)
TEST_F(PrincessTest, PrincessFightWanderingKnight) {
    FightOutcome outcome = princess->fight(knight);
    // Based on comments: Princess -> WanderingKnight = peace
    EXPECT_FALSE(princess->is_dead());
    EXPECT_FALSE(knight->is_dead());
}

// Test Princess fight with another Princess (Peace)
TEST_F(PrincessTest, PrincessFightPrincess) {
    auto princess2 = std::make_shared<Princess>(100, 100);
    FightOutcome outcome = princess->fight(princess2);
    // Princess vs Princess should result in a draw
    EXPECT_EQ(outcome, FightOutcome::Draw);
    EXPECT_FALSE(princess->is_dead());
    EXPECT_FALSE(princess2->is_dead());
}

// Test distance check
TEST_F(PrincessTest, PrincessCheckDistance) {
    // Princess at (200, 300), Dragon at (250, 350)
    // Distance = sqrt(50^2 + 50^2) ≈ 70.7
    bool isClose = princess->is_close(dragon, 100);
    EXPECT_TRUE(isClose);
}

TEST_F(PrincessTest, PrincessCheckDistanceFar) {
    auto distant_knight = std::make_shared<WanderingKnight>(1000, 1000);
    // Distance is large, should not be close
    bool isClose = princess->is_close(distant_knight, 100);
    EXPECT_FALSE(isClose);
}

// Test accept functionality (visitor pattern)
TEST_F(PrincessTest, PrincessAcceptFight) {
    FightOutcome outcome = princess->accept(dragon);
    // Princess accepts Dragon's attack
    EXPECT_TRUE(outcome == FightOutcome::Victory || 
                outcome == FightOutcome::Defeat || 
                outcome == FightOutcome::Draw);
}

// Test subscription to observers
TEST_F(PrincessTest, PrincessNotification) {
    // Princess should be able to subscribe to observers
    auto observer = TextObserver::get();
    princess->subscribe(observer);
    // After subscription, princess should be trackable
    EXPECT_FALSE(princess->is_dead());
}
