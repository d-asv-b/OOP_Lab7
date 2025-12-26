#include "../../include/npc/NPC.hpp"
#include "../../include/observers/FightFileObserver.hpp"
#include "../../include/application/PrintHandler.hpp"

#include <fstream>

FightFileObserver::~FightFileObserver() {
    if (this->out.is_open()) {
        this->out.close();
    }
}

std::shared_ptr<IFightObserver> FightFileObserver::get() {
    static FightFileObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*){});
}

void FightFileObserver::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, FightOutcome outcome) {
    if (this->out.is_open()) {
        this->out << attacker.get()->info() << " напал на " << defender.get()->info() << ". Результат: ";
        switch (outcome) {
            case FightOutcome::Draw: {
                this->out << "ничья.";
                break;
            };
            case FightOutcome::Defeat: {
                this->out << "поражение.";
                break;
            };
            case FightOutcome::MutualDefeat: {
                PrintHandler::print("обоюдное поражение.");
                break;
            }
            case FightOutcome::Victory: {
                this->out << "победа.";
                break;
            }
        }

        this->out << std::endl;
    }
}
