#pragma once

#include "../npc/NPC.hpp"

#include <memory>
#include <vector>

class AppState {
private:
    std::vector<std::shared_ptr<NPC>> characters_;

public:
    AppState() = default;

    std::vector<std::shared_ptr<NPC>>& getCharacters();

    const std::vector<std::shared_ptr<NPC>>& getCharacters() const;

    void setCharacters(const std::vector<std::shared_ptr<NPC>>& chars);
    bool hasCharacters() const;
    void clear();
};
