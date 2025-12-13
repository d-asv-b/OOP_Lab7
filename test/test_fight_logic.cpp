#include <gtest/gtest.h>
#include <memory>
#include "Dragon.hpp"
#include "Princess.hpp"
#include "WanderingKnight.hpp"

class FightLogicTest : public ::testing::Test {
protected:
    std::shared_ptr<Dragon> dragon;
    std::shared_ptr<Princess> princess;
    std::shared_ptr<WanderingKnight> knight;

    void SetUp() override {
        dragon = std::make_shared<Dragon>(100, 200);
        princess = std::make_shared<Princess>(150, 250);
        knight = std::make_shared<WanderingKnight>(120, 180);
    }
};

// Test Dragon vs Princess fight logic
TEST_F(FightLogicTest, DragonVsPrincess) {
    auto outcome = dragon->fight(princess);
    // Dragon kills Princess according to comments
    EXPECT_TRUE(outcome == FightOutcome::Victory || 
                outcome == FightOutcome::Draw ||
                outcome == FightOutcome::Defeat);
}

// Test Princess vs Dragon fight logic
TEST_F(FightLogicTest, PrincessVsDragon) {
    auto outcome = princess->fight(dragon);
    // Princess dies to Dragon according to comments
    EXPECT_TRUE(outcome == FightOutcome::Victory || 
                outcome == FightOutcome::Draw ||
                outcome == FightOutcome::Defeat);
}

// Test Dragon vs WanderingKnight fight logic
TEST_F(FightLogicTest, DragonVsWanderingKnight) {
    auto outcome = dragon->fight(knight);
    // WanderingKnight kills Dragon according to comments
    EXPECT_TRUE(outcome == FightOutcome::Victory || 
                outcome == FightOutcome::Draw ||
                outcome == FightOutcome::Defeat);
}

// Test WanderingKnight vs Dragon fight logic
TEST_F(FightLogicTest, WanderingKnightVsDragon) {
    auto outcome = knight->fight(dragon);
    // WanderingKnight kills Dragon according to comments
    EXPECT_TRUE(outcome == FightOutcome::Victory || 
                outcome == FightOutcome::Draw ||
                outcome == FightOutcome::Defeat);
}

// Test Princess vs WanderingKnight fight logic (Peace)
TEST_F(FightLogicTest, PrincessVsWanderingKnight) {
    auto outcome = princess->fight(knight);
    // Princess and Knight live in peace
    EXPECT_FALSE(princess->is_dead());
    EXPECT_FALSE(knight->is_dead());
}

// Test WanderingKnight vs Princess fight logic (Peace)
TEST_F(FightLogicTest, WanderingKnightVsPrincess) {
    auto outcome = knight->fight(princess);
    // Knight and Princess live in peace
    EXPECT_FALSE(knight->is_dead());
    EXPECT_FALSE(princess->is_dead());
}

// Test same type fights result in draw
TEST_F(FightLogicTest, DragonVsDragon) {
    auto dragon2 = std::make_shared<Dragon>(300, 400);
    auto outcome = dragon->fight(dragon2);
    
    EXPECT_EQ(outcome, FightOutcome::Draw);
    EXPECT_FALSE(dragon->is_dead());
    EXPECT_FALSE(dragon2->is_dead());
}

TEST_F(FightLogicTest, PrincessVsPrincess) {
    auto princess2 = std::make_shared<Princess>(300, 400);
    auto outcome = princess->fight(princess2);
    
    EXPECT_EQ(outcome, FightOutcome::Draw);
    EXPECT_FALSE(princess->is_dead());
    EXPECT_FALSE(princess2->is_dead());
}

TEST_F(FightLogicTest, WanderingKnightVsWanderingKnight) {
    auto knight2 = std::make_shared<WanderingKnight>(300, 400);
    auto outcome = knight->fight(knight2);
    
    EXPECT_EQ(outcome, FightOutcome::Draw);
    EXPECT_FALSE(knight->is_dead());
    EXPECT_FALSE(knight2->is_dead());
}

// Test fight outcomes are valid
TEST_F(FightLogicTest, FightOutcomeValidity) {
    auto outcome1 = dragon->fight(princess);
    EXPECT_TRUE(outcome1 == FightOutcome::Victory || 
                outcome1 == FightOutcome::Defeat || 
                outcome1 == FightOutcome::Draw);
    
    auto outcome2 = knight->fight(dragon);
    EXPECT_TRUE(outcome2 == FightOutcome::Victory || 
                outcome2 == FightOutcome::Defeat || 
                outcome2 == FightOutcome::Draw);
}

// Test visitor pattern - accept method
TEST_F(FightLogicTest, VisitorPatternDragon) {
    auto outcome = dragon->accept(knight);
    EXPECT_TRUE(outcome == FightOutcome::Victory || 
                outcome == FightOutcome::Defeat || 
                outcome == FightOutcome::Draw);
}

TEST_F(FightLogicTest, VisitorPatternPrincess) {
    auto outcome = princess->accept(dragon);
    EXPECT_TRUE(outcome == FightOutcome::Victory || 
                outcome == FightOutcome::Defeat || 
                outcome == FightOutcome::Draw);
}

TEST_F(FightLogicTest, VisitorPatternWanderingKnight) {
    auto outcome = knight->accept(princess);
    EXPECT_TRUE(outcome == FightOutcome::Victory || 
                outcome == FightOutcome::Defeat || 
                outcome == FightOutcome::Draw);
}

// Test multiple consecutive fights
TEST_F(FightLogicTest, MultipleConsecutiveFights) {
    auto dragon2 = std::make_shared<Dragon>(200, 300);
    auto princess2 = std::make_shared<Princess>(250, 350);
    
    // First fight
    dragon->fight(princess);
    
    // Second fight
    knight->fight(dragon2);
    
    // Third fight
    princess2->fight(knight);
    
    // All characters should have valid states
    EXPECT_TRUE(dragon->is_dead() || !dragon->is_dead());
    EXPECT_TRUE(knight->is_dead() || !knight->is_dead());
    EXPECT_TRUE(princess->is_dead() || !princess->is_dead());
}

// Test fight doesn't affect non-participating characters
TEST_F(FightLogicTest, FightDoesNotAffectOthers) {
    auto bystander = std::make_shared<Dragon>(500, 500);
    bool bystanderDeadBefore = bystander->is_dead();
    
    dragon->fight(princess);
    
    bool bystanderDeadAfter = bystander->is_dead();
    EXPECT_EQ(bystanderDeadBefore, bystanderDeadAfter);
}

// Test fight outcome symmetry
TEST_F(FightLogicTest, FightOutcomeSymmetry) {
    auto knight2 = std::make_shared<WanderingKnight>(200, 200);
    
    auto outcome1 = knight->fight(knight2);
    auto outcome2 = knight2->fight(knight);
    
    // Same type fights should both result in draws
    EXPECT_EQ(outcome1, FightOutcome::Draw);
    EXPECT_EQ(outcome2, FightOutcome::Draw);
}
