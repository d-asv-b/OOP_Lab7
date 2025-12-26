#include <gtest/gtest.h>
#include <memory>
#include "../include/application/AppState.hpp"
#include "../include/npc/Dragon.hpp"
#include "../include/npc/Princess.hpp"
#include "../include/npc/WanderingKnight.hpp"

class AppStateTest : public ::testing::Test {
protected:
    AppState appState;
    std::shared_ptr<Dragon> dragon;
    std::shared_ptr<Princess> princess;
    std::shared_ptr<WanderingKnight> knight;

    void SetUp() override {
        dragon = std::make_shared<Dragon>(100, 200);
        princess = std::make_shared<Princess>(150, 250);
        knight = std::make_shared<WanderingKnight>(300, 400);
    }
};

// Test AppState creation
TEST_F(AppStateTest, CreateAppState) {
    EXPECT_FALSE(appState.hasCharacters());
}

// Test AppState is initially empty
TEST_F(AppStateTest, AppStateInitiallyEmpty) {
    EXPECT_EQ(appState.getCharacters().size(), 0);
    EXPECT_FALSE(appState.hasCharacters());
}

// Test set single character
TEST_F(AppStateTest, SetSingleCharacter) {
    std::vector<std::shared_ptr<NPC>> characters = {dragon};
    appState.setCharacters(characters);
    
    EXPECT_TRUE(appState.hasCharacters());
    EXPECT_EQ(appState.getCharacters().size(), 1);
    EXPECT_EQ(appState.getCharacters()[0], dragon);
}

// Test set multiple characters
TEST_F(AppStateTest, SetMultipleCharacters) {
    std::vector<std::shared_ptr<NPC>> characters = {dragon, princess, knight};
    appState.setCharacters(characters);
    
    EXPECT_TRUE(appState.hasCharacters());
    EXPECT_EQ(appState.getCharacters().size(), 3);
}

// Test get characters returns correct order
TEST_F(AppStateTest, GetCharactersOrder) {
    std::vector<std::shared_ptr<NPC>> characters = {dragon, princess, knight};
    appState.setCharacters(characters);
    
    auto retrieved = appState.getCharacters();
    EXPECT_EQ(retrieved[0], dragon);
    EXPECT_EQ(retrieved[1], princess);
    EXPECT_EQ(retrieved[2], knight);
}

// Test clear characters
TEST_F(AppStateTest, ClearCharacters) {
    std::vector<std::shared_ptr<NPC>> characters = {dragon, princess, knight};
    appState.setCharacters(characters);
    
    EXPECT_TRUE(appState.hasCharacters());
    
    appState.clear();
    
    EXPECT_FALSE(appState.hasCharacters());
    EXPECT_EQ(appState.getCharacters().size(), 0);
}

// Test const get characters
TEST_F(AppStateTest, ConstGetCharacters) {
    std::vector<std::shared_ptr<NPC>> characters = {dragon, princess, knight};
    appState.setCharacters(characters);
    
    const auto& retrieved = appState.getCharacters();
    EXPECT_EQ(retrieved.size(), 3);
}

// Test modifying characters through getCharacters
TEST_F(AppStateTest, ModifyCharactersThroughGet) {
    std::vector<std::shared_ptr<NPC>> characters = {dragon, princess};
    appState.setCharacters(characters);
    
    auto& mutableChars = appState.getCharacters();
    mutableChars.push_back(knight);
    
    EXPECT_EQ(appState.getCharacters().size(), 3);
}

// Test hasCharacters with empty state
TEST_F(AppStateTest, HasCharactersEmpty) {
    EXPECT_FALSE(appState.hasCharacters());
}

// Test hasCharacters with populated state
TEST_F(AppStateTest, HasCharactersPopulated) {
    std::vector<std::shared_ptr<NPC>> characters = {dragon};
    appState.setCharacters(characters);
    
    EXPECT_TRUE(appState.hasCharacters());
}

// Test replacing characters
TEST_F(AppStateTest, ReplaceCharacters) {
    std::vector<std::shared_ptr<NPC>> characters1 = {dragon, princess};
    appState.setCharacters(characters1);
    EXPECT_EQ(appState.getCharacters().size(), 2);
    
    std::vector<std::shared_ptr<NPC>> characters2 = {knight};
    appState.setCharacters(characters2);
    EXPECT_EQ(appState.getCharacters().size(), 1);
    EXPECT_EQ(appState.getCharacters()[0], knight);
}

// Test clear removes all characters
TEST_F(AppStateTest, ClearRemovesAll) {
    std::vector<std::shared_ptr<NPC>> characters = {dragon, princess, knight};
    appState.setCharacters(characters);
    EXPECT_EQ(appState.getCharacters().size(), 3);
    
    appState.clear();
    EXPECT_EQ(appState.getCharacters().size(), 0);
}

// Test state can hold large number of characters
TEST_F(AppStateTest, LargeCharacterCount) {
    std::vector<std::shared_ptr<NPC>> characters;
    
    for (int i = 0; i < 100; i++) {
        characters.push_back(std::make_shared<Dragon>(i, i));
    }
    
    appState.setCharacters(characters);
    EXPECT_EQ(appState.getCharacters().size(), 100);
}

// Test empty set clears previous characters
TEST_F(AppStateTest, SetEmptyClears) {
    std::vector<std::shared_ptr<NPC>> characters = {dragon, princess};
    appState.setCharacters(characters);
    EXPECT_TRUE(appState.hasCharacters());
    
    std::vector<std::shared_ptr<NPC>> empty;
    appState.setCharacters(empty);
    EXPECT_FALSE(appState.hasCharacters());
}
