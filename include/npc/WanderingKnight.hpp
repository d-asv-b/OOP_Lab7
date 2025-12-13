#pragma once

#include <cstddef>
#include <istream>

#include "NPC.hpp"

//    Interaction table
// Princess         - peace
// Dragon           - kill
// Wandering Knight - peace

//       Stats table
// Move             - 30
// Kill distance    - 10

#define WANDERING_KNIGHT_MOVE_DISTANCE  = 30
#define WANDERING_KNIGHT_FIGHT_DISTANCE = 10

class WanderingKnight : public NPC {
public:
    WanderingKnight(long coord_X, long coord_Y);
    WanderingKnight(std::istream& input);

    virtual void print() const override;
    virtual std::string info() const override;
};