#include "../../include/npc/Dragon.hpp"
#include "../../include/npc/Princess.hpp"

#include <iostream>
#include <memory>
#include <sstream>


Dragon::Dragon(long pos_X, long pos_Y) 
    : NPC(NPC_Type::Dragon, pos_X, pos_Y) {
}

Dragon::Dragon(std::istream& input) 
    : NPC(NPC_Type::Dragon, input) {
}

std::string Dragon::info() const {
    std::stringstream info_stream;
    info_stream << "[NPC { type: Dragon, X: " << this->x_ << ", Y: " << this->y_ << " }]";

    return info_stream.str();
}

void Dragon::print() const {
    std::cout << this->info() << std::endl;
}