#include "../../include/npc/NPC.hpp"
#include "../../include/observers/FightTextObserver.hpp"
#include "../../include/application/PrintHandler.hpp"

#include <sstream>

std::shared_ptr<IFightObserver> FightTextObserver::get() {
    static FightTextObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
}

void FightTextObserver::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, FightOutcome outcome) {
    std::stringstream ss;
    ss << "\t\t" << attacker.get()->info() << " напал на " << defender.get()->info() << ". Результат: ";

    switch (outcome) {
        case FightOutcome::Draw: {
            ss << "ничья.";
            break;
        };
        case FightOutcome::Defeat: {
            ss << "поражение.";
            break;
        };
        case FightOutcome::MutualDefeat: {
            ss << "обоюдное поражение.";
            break;
        }
        case FightOutcome::Victory: {
            ss << "победа.";
            break;
        }
    }

    ss << std::endl;
    PrintHandler::print(ss);
}
