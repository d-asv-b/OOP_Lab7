#pragma once

#include <cstddef>
#include <istream>
#include <memory>

#include "NPC.hpp"

//    Interaction table
// Princess         - kill
// Dragon           - peace
// Wandering Knight - death

//       Stats table
// Move             - 50
// Kill distance    - 30

#define DRAGON_MOVE_DISTANCE  = 50
#define DRAGON_FIGHT_DISTANCE = 30

class Dragon : public NPC {
public:
    Dragon(long coord_X, long coord_Y);
    Dragon(std::istream& input);

    virtual void print() const override;
    virtual std::string info() const override;
};