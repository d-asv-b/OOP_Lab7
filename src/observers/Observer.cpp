#include "../../include/npc/NPC.hpp"
#include "../../include/observers/Observer.hpp"

#include <iostream>

std::shared_ptr<IFightObserver> TextObserver::get() {
    static TextObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
}

void TextObserver::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, FightOutcome outcome) {
    std::cout << "\t\t" << attacker.get()->info() << " напал на " << defender.get()->info() << ". Результат: ";

    switch (outcome) {
        case FightOutcome::Draw: {
            std::cout << "ничья.";
            break;
        };
        case FightOutcome::Defeat: {
            std::cout << "поражение.";
            break;
        };
        case FightOutcome::MutualDefeat: {
            std::cout << "обоюдное поражение.";
            break;
        }
        case FightOutcome::Victory: {
            std::cout << "победа.";
            break;
        }
    }

    std::cout << std::endl;
}