#include "../../include/npc/NPC.hpp"
#include "../../include/observers/DiceTextObserver.hpp"
#include "../../include/application/PrintHandler.hpp"

#include <sstream>
#include <string>

std::shared_ptr<IDiceObserver> DiceTextObserver::get() {
    static DiceTextObserver instance_;
    return std::shared_ptr<IDiceObserver>(&instance_, [](IDiceObserver*){});
}

void DiceTextObserver::on_throw_dice(const std::shared_ptr<NPC> npc, const std::string &value_name, const char value) const {
    std::stringstream ss;

    ss << "\t\t" << npc->info();
    ss << " подкинул кубик на " << value_name << " и получил " << std::to_string(value) << " очков!\n";

    PrintHandler::print(ss.str());
}