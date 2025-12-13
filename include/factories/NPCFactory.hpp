#pragma once

#include <cstddef>
#include <memory>

#include "../npc/NPC.hpp"

class NPCFactory {
public:
    std::shared_ptr<NPC> createNPC(std::istream& input);

    std::shared_ptr<NPC> createNPC(NPC_Type type, long coord_X, long coord_Y);
};