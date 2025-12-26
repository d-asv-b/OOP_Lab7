#pragma once

#include "./IObservers.hpp"

class FightFileObserver : public IFightObserver {
private:
    std::ofstream out;
    FightFileObserver() = default;
public:
    ~FightFileObserver();

    static std::shared_ptr<IFightObserver> get();

    virtual void on_fight(const std::shared_ptr<NPC> npc_1, const std::shared_ptr<NPC> npc_2, FightOutcome outcome) override final;
};