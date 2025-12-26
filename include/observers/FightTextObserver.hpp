#pragma once

#include "./IObservers.hpp"

class FightTextObserver : public IFightObserver {
private:
    FightTextObserver() = default;
public:
    static std::shared_ptr<IFightObserver> get();

    virtual void on_fight(const std::shared_ptr<NPC> npc_1, const std::shared_ptr<NPC> npc_2, FightOutcome outcome) override final;
};