#include "../../include/npc/Princess.hpp"
#include "../../include/application/PrintHandler.hpp"
#include "../../include/application/AppLogic.hpp"

#include <iostream>
#include <memory>
#include <sstream>

Princess::Princess(long pos_X, long pos_Y)
    : NPC(NPC_Type::Princess, pos_X, pos_Y) {
        symbol_ = 'P';
        move_distance_ = 1;
        fight_distance_ = 1;
}

Princess::Princess(std::istream& input)
    : NPC(NPC_Type::Princess, input) {
        symbol_ = 'P';
}

std::string Princess::info() const {
    std::stringstream info_stream;
    info_stream << "[NPC { type: Princess, X: " << this->x_ << ", Y: " << this->y_ << " }]";

    return info_stream.str();
}

void Princess::print() const {
    std::stringstream ss;
    ss << this->info() << std::endl;
    PrintHandler::print(ss);
}

FightOutcome Princess::accept(std::shared_ptr<NPC> attacker) {
    return attacker->fight(std::dynamic_pointer_cast<Princess>(shared_from_this()));
} 

FightOutcome Princess::fight(std::shared_ptr<WanderingKnight> other) {
    return FightOutcome::Draw;
}

FightOutcome Princess::fight(std::shared_ptr<Princess> other) {
    return FightOutcome::Draw;
}

FightOutcome Princess::fight(std::shared_ptr<Dragon> other) {
    int this_defense   = tossD6();
    this->notify("'защита'", this_defense);

    int defender_strength  = tossD6();
    this->notify("'сила'", defender_strength);

    if (this_defense < defender_strength) {
        this->kill();
        return FightOutcome::Defeat;
    }

    return FightOutcome::Draw;
}