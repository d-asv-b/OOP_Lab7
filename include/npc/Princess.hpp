#pragma once

#include <cstddef>
#include <istream>
#include <memory>

#include "NPC.hpp"

//    Interaction table
// Princess         - peace
// Dragon           - peace
// Wandering Knight - peace

//       Stats table
// Move             - 1
// Kill distance    - 1

#define PRINCESS_MOVE_DISTANCE  = 1
#define PRINCESS_FIGHT_DISTANCE = 1

class Princess : public NPC {
public:
    Princess(long coord_X, long coord_Y);
    Princess(std::istream& input);

    virtual void print() const override;
    virtual std::string info() const override;
};