#include "../../include/npc/Princess.hpp"

#include <iostream>
#include <memory>
#include <sstream>

Princess::Princess(long pos_X, long pos_Y)
    : NPC(NPC_Type::Princess, pos_X, pos_Y) {
}

Princess::Princess(std::istream& input)
    : NPC(NPC_Type::Princess, input) {
}

std::string Princess::info() const {
    std::stringstream info_stream;
    info_stream << "[NPC { type: Princess, X: " << this->x_ << ", Y: " << this->y_ << " }]";

    return info_stream.str();
}

void Princess::print() const {
    std::cout << this->info() << std::endl;
}