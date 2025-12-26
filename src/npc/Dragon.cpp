#include "../../include/npc/Dragon.hpp"
#include "../../include/npc/Princess.hpp"
#include "../../include/application/PrintHandler.hpp"
#include "../../include/application/AppLogic.hpp"

#include <iostream>
#include <memory>
#include <sstream>

Dragon::Dragon(long pos_X, long pos_Y) 
    : NPC(NPC_Type::Dragon, pos_X, pos_Y) {
        symbol_ = 'D';
        move_distance_ = 50;
        fight_distance_ = 30;
}

Dragon::Dragon(std::istream& input) 
    : NPC(NPC_Type::Dragon, input) {
        symbol_ = 'D';
        move_distance_ = 50;
        fight_distance_ = 30;
}

std::string Dragon::info() const {
    std::stringstream info_stream;
    info_stream << "[NPC { type: Dragon, X: " << this->x_ << ", Y: " << this->y_ << " }]";

    return info_stream.str();
}

void Dragon::print() const {
    std::stringstream ss;
    ss << this->info() << std::endl;
    PrintHandler::print(ss);
}

FightOutcome Dragon::accept(std::shared_ptr<NPC> attacker) {
    return attacker->fight(std::dynamic_pointer_cast<Dragon>(shared_from_this()));
} 

FightOutcome Dragon::fight(std::shared_ptr<WanderingKnight> other) {
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

FightOutcome Dragon::fight(std::shared_ptr<Princess> other) {
    int this_strength  = tossD6();
    this->notify("'сила'", this_strength);

    int defender_defense   = tossD6();
    this->notify("'защита'", defender_defense);

    if (this_strength > defender_defense) {
        other->kill();

        return FightOutcome::Victory;
    }

    return FightOutcome::Draw;
}

FightOutcome Dragon::fight(std::shared_ptr<Dragon> other) {
    return FightOutcome::Draw;
}