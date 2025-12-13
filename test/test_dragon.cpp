#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include "Dragon.hpp"
#include "Princess.hpp"
#include "WanderingKnight.hpp"

class DragonTest : public ::testing::Test {
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

// Test Dragon creation and basic properties
TEST_F(DragonTest, CreateDragon) {
    EXPECT_FALSE(dragon->is_dead());
}

// Test Dragon kill functionality
TEST_F(DragonTest, DragonCanBeKilled) {
    EXPECT_FALSE(dragon->is_dead());
    dragon->kill();
    EXPECT_TRUE(dragon->is_dead());
}

// Test Dragon fight with Princess (Victory)
TEST_F(DragonTest, DragonFightPrincess) {
    FightOutcome outcome = dragon->fight(princess);

    EXPECT_EQ(outcome, FightOutcome::Victory);

    EXPECT_FALSE(dragon->is_dead());
    EXPECT_TRUE(princess->is_dead());
}

// Test Dragon fight with WanderingKnight (Defeat)
TEST_F(DragonTest, DragonFightWanderingKnight) {
    FightOutcome outcome = dragon->fight(knight);

    EXPECT_EQ(outcome, FightOutcome::Defeat);

    EXPECT_FALSE(knight->is_dead());
    EXPECT_TRUE(dragon->is_dead());
}

// Test Dragon fight with another Dragon (Draw)
TEST_F(DragonTest, DragonFightDragon) {
    auto dragon2 = std::make_shared<Dragon>(300, 400);
    FightOutcome outcome = dragon->fight(dragon2);
    
    EXPECT_EQ(outcome, FightOutcome::Draw);

    EXPECT_FALSE(dragon->is_dead());
    EXPECT_FALSE(dragon2->is_dead());
}

// Test distance check
TEST_F(DragonTest, DragonCheckDistance) {
    // Dragon at (100, 200), Princess at (150, 250)
    // Distance calculation: sqrt((150-100)^2 + (250-200)^2) = sqrt(50^2 + 50^2) ≈ 70.7s
    bool isClose = dragon->is_close(princess, 100);
    EXPECT_TRUE(isClose);
}

TEST_F(DragonTest, DragonCheckDistanceFar) {
    auto distant_princess = std::make_shared<Princess>(500, 500);
    // Distance > 100, should not be close
    bool isClose = dragon->is_close(distant_princess, 100);
    EXPECT_FALSE(isClose);
}

// Test accept functionality (visitor pattern)
TEST_F(DragonTest, DragonAcceptFight) {
    FightOutcome outcome = dragon->accept(knight);
    EXPECT_TRUE(outcome == FightOutcome::Victory || 
                outcome == FightOutcome::Defeat || 
                outcome == FightOutcome::Draw);
}
