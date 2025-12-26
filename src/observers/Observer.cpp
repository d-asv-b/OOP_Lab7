#include "../../include/npc/NPC.hpp"
#include "../../include/observers/Observer.hpp"
#include "../../include/application/PrintHandler.hpp"

#include <iostream>
#include <sstream>

std::shared_ptr<IFightObserver> TextObserver::get() {
    static TextObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
}

void TextObserver::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, FightOutcome outcome) {
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

FileObserver::~FileObserver() {
    if (this->out.is_open()) {
        this->out.close();
    }
}

std::shared_ptr<IFightObserver> FileObserver::get() {
    static FileObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*){});
}

void FileObserver::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, FightOutcome outcome) {
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