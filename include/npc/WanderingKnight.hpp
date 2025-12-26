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

    virtual FightOutcome accept(std::shared_ptr<NPC> visitor) override;

    virtual FightOutcome fight(std::shared_ptr<WanderingKnight> defender) override;
    virtual FightOutcome fight(std::shared_ptr<Princess> defender) override;
    virtual FightOutcome fight(std::shared_ptr<Dragon> defender) override;
};