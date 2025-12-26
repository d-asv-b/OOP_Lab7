#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include "../include/npc/Dragon.hpp"
#include "../include/npc/Princess.hpp"
#include "../include/npc/WanderingKnight.hpp"

class NPCConcreteTest : public ::testing::Test {
protected:
    std::shared_ptr<Dragon> dragon;
    std::shared_ptr<Princess> princess;
    std::shared_ptr<WanderingKnight> knight;

    void SetUp() override {
        dragon = std::make_shared<Dragon>(100, 200);
        princess = std::make_shared<Princess>(150, 250);
        knight = std::make_shared<WanderingKnight>(300, 400);
    }
};

// Test Dragon vs Dragon (should always be Draw)
TEST_F(NPCConcreteTest, DragonVsDragon) {
    FightOutcome result = dragon->fight(dragon);
    EXPECT_EQ(result, FightOutcome::Draw);
}

// Test Dragon vs Princess (Dragon should kill Princess or Draw)
TEST_F(NPCConcreteTest, DragonVsPrincess) {
    FightOutcome result = dragon->fight(princess);
    EXPECT_TRUE(result == FightOutcome::Victory || result == FightOutcome::Draw);

    if (result == FightOutcome::Victory) {
        EXPECT_TRUE(princess->is_dead());
        EXPECT_FALSE(dragon->is_dead());
    }
}

// Test Dragon vs Knight (Knight should kill Dragon or Draw)
TEST_F(NPCConcreteTest, DragonVsKnight) {
    FightOutcome result = dragon->fight(knight);
    EXPECT_TRUE(result == FightOutcome::Defeat || result == FightOutcome::Draw);

    if (result == FightOutcome::Defeat) {
        EXPECT_TRUE(dragon->is_dead());
        EXPECT_FALSE(knight->is_dead());
    }
}

// Test Princess vs Dragon (Princess should be killed or Draw)
TEST_F(NPCConcreteTest, PrincessVsDragon) {
    FightOutcome result = princess->fight(dragon);
    EXPECT_TRUE(result == FightOutcome::Defeat || result == FightOutcome::Draw);

    if (result == FightOutcome::Defeat) {
        EXPECT_TRUE(princess->is_dead());
        EXPECT_FALSE(dragon->is_dead());
    }
}

// Test Princess vs Princess (should always be Draw)
TEST_F(NPCConcreteTest, PrincessVsPrincess) {
    FightOutcome result = princess->fight(princess);
    EXPECT_EQ(result, FightOutcome::Draw);
}

// Test Princess vs Knight (Knight should kill Princess or Draw)
TEST_F(NPCConcreteTest, PrincessVsKnight) {
    FightOutcome result = princess->fight(knight);
    EXPECT_TRUE(result == FightOutcome::Defeat || result == FightOutcome::Draw);

    if (result == FightOutcome::Defeat) {
        EXPECT_TRUE(princess->is_dead());
        EXPECT_FALSE(knight->is_dead());
    }
}

// Test Knight vs Dragon (Knight should kill Dragon or Draw)
TEST_F(NPCConcreteTest, KnightVsDragon) {
    FightOutcome result = knight->fight(dragon);
    EXPECT_TRUE(result == FightOutcome::Victory || result == FightOutcome::Draw);

    if (result == FightOutcome::Victory) {
        EXPECT_TRUE(dragon->is_dead());
        EXPECT_FALSE(knight->is_dead());
    }
}

// Test Knight vs Princess (Knight should kill Princess or Draw)
TEST_F(NPCConcreteTest, KnightVsPrincess) {
    FightOutcome result = knight->fight(princess);
    EXPECT_TRUE(result == FightOutcome::Victory || result == FightOutcome::Draw);

    if (result == FightOutcome::Victory) {
        EXPECT_TRUE(princess->is_dead());
        EXPECT_FALSE(knight->is_dead());
    }
}

// Test Knight vs Knight (should always be Draw)
TEST_F(NPCConcreteTest, KnightVsKnight) {
    FightOutcome result = knight->fight(knight);
    EXPECT_EQ(result, FightOutcome::Draw);
}

// Test accept method - Dragon
TEST_F(NPCConcreteTest, DragonAccept) {
    auto attacker = std::make_shared<WanderingKnight>(130, 230);
    FightOutcome result = dragon->accept(attacker);
    EXPECT_TRUE(result == FightOutcome::Victory || result == FightOutcome::Draw);

    if (result == FightOutcome::Victory) {
        EXPECT_TRUE(dragon->is_dead());
        EXPECT_FALSE(attacker->is_dead());
    }
}

// Test accept method - Princess
TEST_F(NPCConcreteTest, PrincessAccept) {
    auto attacker = std::make_shared<Dragon>(160, 260);
    FightOutcome result = princess->accept(attacker);
    std::cout << (int)result;
    EXPECT_TRUE(result == FightOutcome::Victory || result == FightOutcome::Draw);

    if (result == FightOutcome::Defeat) {
        EXPECT_TRUE(princess->is_dead());
        EXPECT_FALSE(attacker->is_dead());
    }
}

// Test accept method - Knight
TEST_F(NPCConcreteTest, KnightAccept) {
    auto attacker = std::make_shared<Princess>(310, 410);
    FightOutcome result = knight->accept(attacker);
    EXPECT_TRUE(result == FightOutcome::Victory || result == FightOutcome::Draw);

    if (result == FightOutcome::Victory) {
        EXPECT_TRUE(attacker->is_dead());
        EXPECT_FALSE(knight->is_dead());
    }
}

// Test Dragon properties
TEST_F(NPCConcreteTest, DragonProperties) {
    EXPECT_EQ(dragon->get_symbol(), 'D');
    EXPECT_EQ(dragon->get_move_distance(), 50);
    EXPECT_EQ(dragon->get_fight_distance(), 30);
    EXPECT_FALSE(dragon->info().empty());
    EXPECT_NE(dragon->info().find("Dragon"), std::string::npos);
}

// Test Princess properties
TEST_F(NPCConcreteTest, PrincessProperties) {
    EXPECT_EQ(princess->get_symbol(), 'P');
    EXPECT_EQ(princess->get_move_distance(), 1);
    EXPECT_EQ(princess->get_fight_distance(), 1);
    EXPECT_FALSE(princess->info().empty());
    EXPECT_NE(princess->info().find("Princess"), std::string::npos);
}

// Test Knight properties
TEST_F(NPCConcreteTest, KnightProperties) {
    EXPECT_EQ(knight->get_symbol(), 'K');
    EXPECT_EQ(knight->get_move_distance(), 30);
    EXPECT_EQ(knight->get_fight_distance(), 10);
    EXPECT_FALSE(knight->info().empty());
    EXPECT_NE(knight->info().find("WanderingKnight"), std::string::npos);
}

// Test NPC creation from stream
TEST_F(NPCConcreteTest, CreateFromStream) {
    std::stringstream ss("500 600");
    auto dragonFromStream = std::make_shared<Dragon>(ss);
    EXPECT_EQ(dragonFromStream->get_position().first, 500);
    EXPECT_EQ(dragonFromStream->get_position().second, 600);
    EXPECT_EQ(dragonFromStream->get_symbol(), 'D');
}
