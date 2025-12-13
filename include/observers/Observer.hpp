#pragma once

#include <memory>

class NPC;
enum struct FightOutcome : int;

class IFightObserver {
public:
    virtual void on_fight(const std::shared_ptr<NPC> npc_1, const std::shared_ptr<NPC> npc_2, FightOutcome outcome) = 0;
};

class TextObserver : public IFightObserver {
public:
    TextObserver() = default;

    static std::shared_ptr<IFightObserver> get();

    virtual void on_fight(const std::shared_ptr<NPC> npc_1, const std::shared_ptr<NPC> npc_2, FightOutcome outcome) override;
};
