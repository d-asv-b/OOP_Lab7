#include "../../include/npc/WanderingKnight.hpp"
#include "../../include/npc/Dragon.hpp"

#include <iostream>
#include <sstream>

WanderingKnight::WanderingKnight(long pos_X, long pos_Y)
    : NPC(NPC_Type::WanderingKnight, pos_X, pos_Y) {
}

WanderingKnight::WanderingKnight(std::istream& input)
    : NPC(NPC_Type::WanderingKnight, input) {
}

std::string WanderingKnight::info() const {
    std::stringstream info_stream;
    info_stream << "[NPC { type: WanderingKnight, X: " << this->x_ << ", Y: " << this->y_ << " }]";

    return info_stream.str();
}

void WanderingKnight::print() const {
    std::cout << this->info() << std::endl;
}