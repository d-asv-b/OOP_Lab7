#include "../../include/npc/WanderingKnight.hpp"
#include "../../include/npc/Dragon.hpp"
#include "../../include/application/PrintHandler.hpp"
#include "../../include/application/AppLogic.hpp"

#include <iostream>
#include <sstream>

WanderingKnight::WanderingKnight(long pos_X, long pos_Y)
    : NPC(NPC_Type::WanderingKnight, pos_X, pos_Y) {
        symbol_ = 'K';
        move_distance_ = 30;
        fight_distance_ = 10;
}

WanderingKnight::WanderingKnight(std::istream& input)
    : NPC(NPC_Type::WanderingKnight, input) {
        symbol_ = 'K';
        move_distance_ = 30;
        fight_distance_ = 10;
}

std::string WanderingKnight::info() const {
    std::stringstream info_stream;
    info_stream << "[NPC { type: WanderingKnight, X: " << this->x_ << ", Y: " << this->y_ << " }]";

    return info_stream.str();
}

void WanderingKnight::print() const {
    std::stringstream ss;
    ss << this->info() << std::endl;
    PrintHandler::print(ss);
}

FightOutcome WanderingKnight::accept(std::shared_ptr<NPC> attacker) {
    return attacker->fight(std::dynamic_pointer_cast<WanderingKnight>(shared_from_this()));
} 

FightOutcome WanderingKnight::fight(std::shared_ptr<WanderingKnight> other) {
    return FightOutcome::Draw;
}

FightOutcome WanderingKnight::fight(std::shared_ptr<Princess> other) {
    return FightOutcome::Draw;
}

FightOutcome WanderingKnight::fight(std::shared_ptr<Dragon> other) {
    int this_defense   = tossD6();
    int this_strength  = tossD6();

    int defender_defense   = tossD6();
    int defender_strength  = tossD6();

    if (this_strength > defender_defense) {
        other->kill();

        return FightOutcome::Victory;
    }

    return FightOutcome::Draw;
}