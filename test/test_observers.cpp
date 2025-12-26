#include <gtest/gtest.h>
#include <memory>
#include <fstream>
#include <filesystem>
#include "../include/observers/FightTextObserver.hpp"
#include "../include/observers/FightFileObserver.hpp"
#include "../include/observers/DiceTextObserver.hpp"
#include "../include/npc/Dragon.hpp"
#include "../include/npc/Princess.hpp"

class ObserversTest : public ::testing::Test {
protected:
    std::shared_ptr<Dragon> dragon;
    std::shared_ptr<Princess> princess;

    void SetUp() override {
        dragon = std::make_shared<Dragon>(100, 200);
        princess = std::make_shared<Princess>(150, 250);
    }

    void TearDown() override {
        // Clean up any test files
        std::filesystem::remove("fight_log.txt");
    }
};

// Test FightTextObserver singleton
TEST_F(ObserversTest, FightTextObserverSingleton) {
    auto observer1 = FightTextObserver::get();
    auto observer2 = FightTextObserver::get();

    EXPECT_EQ(observer1, observer2);
    EXPECT_NE(observer1, nullptr);
}

// Test FightTextObserver on_fight method
TEST_F(ObserversTest, FightTextObserverOnFight) {
    auto observer = FightTextObserver::get();

    // Test all fight outcomes
    observer->on_fight(dragon, princess, FightOutcome::Victory);
    observer->on_fight(dragon, princess, FightOutcome::Defeat);
    observer->on_fight(dragon, princess, FightOutcome::Draw);
    observer->on_fight(dragon, princess, FightOutcome::MutualDefeat);

    // Should not crash
    SUCCEED();
}

// Test FightFileObserver singleton
TEST_F(ObserversTest, FightFileObserverSingleton) {
    auto observer1 = FightFileObserver::get();
    auto observer2 = FightFileObserver::get();

    EXPECT_EQ(observer1, observer2);
    EXPECT_NE(observer1, nullptr);
}

// Test FightFileObserver on_fight method
TEST_F(ObserversTest, FightFileObserverOnFight) {
    auto observer = FightFileObserver::get();

    // Test fight outcomes
    observer->on_fight(dragon, princess, FightOutcome::Victory);
    observer->on_fight(dragon, princess, FightOutcome::Defeat);
    observer->on_fight(dragon, princess, FightOutcome::Draw);
    observer->on_fight(dragon, princess, FightOutcome::MutualDefeat);

    // Should not crash
    SUCCEED();
}

// Test DiceTextObserver singleton
TEST_F(ObserversTest, DiceTextObserverSingleton) {
    auto observer1 = DiceTextObserver::get();
    auto observer2 = DiceTextObserver::get();

    EXPECT_EQ(observer1, observer2);
    EXPECT_NE(observer1, nullptr);
}

// Test DiceTextObserver on_throw_dice method
TEST_F(ObserversTest, DiceTextObserverOnThrowDice) {
    auto observer = DiceTextObserver::get();

    // Test various dice throws
    observer->on_throw_dice(dragon, "атака", '5');
    observer->on_throw_dice(princess, "защита", '3');
    observer->on_throw_dice(dragon, "сила", '6');

    // Should not crash
    SUCCEED();
}

// Test DiceTextObserver with different values
TEST_F(ObserversTest, DiceTextObserverDifferentValues) {
    auto observer = DiceTextObserver::get();

    // Test with minimum and maximum dice values
    observer->on_throw_dice(dragon, "минимальный бросок", '1');
    observer->on_throw_dice(dragon, "максимальный бросок", '6');

    // Test with different value names
    observer->on_throw_dice(dragon, "атака", '4');
    observer->on_throw_dice(dragon, "оборона", '2');
    observer->on_throw_dice(dragon, "сила", '6');
}

// Test multiple fight notifications
TEST_F(ObserversTest, MultipleFightNotifications) {
    auto observer = FightTextObserver::get();

    for (int i = 0; i < 5; ++i) {
        observer->on_fight(dragon, princess, FightOutcome::Draw);
    }

    SUCCEED();
}

// Test multiple dice notifications
TEST_F(ObserversTest, MultipleDiceNotifications) {
    auto observer = DiceTextObserver::get();

    for (int i = 1; i <= 6; ++i) {
        std::string value_name = "бросок " + std::to_string(i);
        observer->on_throw_dice(dragon, value_name, static_cast<char>('0' + i));
    }

    SUCCEED();
}

// Test observer interface compliance
TEST_F(ObserversTest, ObserverInterfaceCompliance) {
    auto fightObserver = FightTextObserver::get();
    auto diceObserver = DiceTextObserver::get();

    // Verify they implement the correct interfaces
    IFightObserver* fightInterface = fightObserver.get();
    IDiceObserver* diceInterface = diceObserver.get();

    EXPECT_NE(fightInterface, nullptr);
    EXPECT_NE(diceInterface, nullptr);

    // Test interface methods
    fightInterface->on_fight(dragon, princess, FightOutcome::Draw);
    diceInterface->on_throw_dice(dragon, "test", '5');
}
