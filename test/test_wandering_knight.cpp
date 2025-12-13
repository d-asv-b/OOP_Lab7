#include <gtest/gtest.h>
#include <memory>
#include "WanderingKnight.hpp"
#include "Dragon.hpp"
#include "Princess.hpp"

class WanderingKnightTest : public ::testing::Test {
protected:
    std::shared_ptr<WanderingKnight> knight;
    std::shared_ptr<Dragon> dragon;
    std::shared_ptr<Princess> princess;

    void SetUp() override {
        knight = std::make_shared<WanderingKnight>(300, 400);
        dragon = std::make_shared<Dragon>(350, 450);
        princess = std::make_shared<Princess>(280, 380);
    }
};

// Test WanderingKnight creation and basic properties
TEST_F(WanderingKnightTest, CreateWanderingKnight) {
    EXPECT_FALSE(knight->is_dead());
}

TEST_F(WanderingKnightTest, WanderingKnightInitialInfo) {
    auto info = knight->info();
    EXPECT_FALSE(info.empty());
}

// Test WanderingKnight kill functionality
TEST_F(WanderingKnightTest, WanderingKnightCanBeKilled) {
    EXPECT_FALSE(knight->is_dead());
    knight->kill();
    EXPECT_TRUE(knight->is_dead());
}

// Test WanderingKnight fight with Dragon (Victory)
TEST_F(WanderingKnightTest, WanderingKnightFightDragon) {
    FightOutcome outcome = knight->fight(dragon);
    EXPECT_EQ(outcome, FightOutcome::Victory);

    EXPECT_FALSE(knight->is_dead());
    EXPECT_TRUE(dragon->is_dead());
}

// Test WanderingKnight fight with Princess (Draw)
TEST_F(WanderingKnightTest, WanderingKnightFightPrincess) {
    FightOutcome outcome = knight->fight(princess);

    EXPECT_EQ(outcome, FightOutcome::Draw);

    EXPECT_FALSE(knight->is_dead());
    EXPECT_FALSE(princess->is_dead());
}

// Test WanderingKnight fight with another WanderingKnight (Draw)
TEST_F(WanderingKnightTest, WanderingKnightFightWanderingKnight) {
    auto knight2 = std::make_shared<WanderingKnight>(200, 200);
    FightOutcome outcome = knight->fight(knight2);

    EXPECT_EQ(outcome, FightOutcome::Draw);

    EXPECT_FALSE(knight->is_dead());
    EXPECT_FALSE(knight2->is_dead());
}

// Test distance check
TEST_F(WanderingKnightTest, WanderingKnightCheckDistance) {
    // Knight at (300, 400), Dragon at (350, 450)
    // Distance = sqrt(50^2 + 50^2) ≈ 70.7
    bool isClose = knight->is_close(dragon, 100);
    EXPECT_TRUE(isClose);
}

TEST_F(WanderingKnightTest, WanderingKnightCheckDistanceFar) {
    auto distant_princess = std::make_shared<Princess>(800, 900);
    // Distance is large, should not be close
    bool isClose = knight->is_close(distant_princess, 100);
    EXPECT_FALSE(isClose);
}

// Test accept functionality (visitor pattern)
TEST_F(WanderingKnightTest, WanderingKnightAcceptFight) {
    FightOutcome outcome = knight->accept(dragon);
    // Knight accepts Dragon's attack
    EXPECT_TRUE(outcome == FightOutcome::Victory || 
                outcome == FightOutcome::Defeat || 
                outcome == FightOutcome::Draw);
}
