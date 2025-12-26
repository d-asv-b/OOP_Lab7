#pragma once

#include <fstream>
#include <memory>

class NPC;
enum struct FightOutcome : int;

class IFightObserver {
public:
    virtual void on_fight(const std::shared_ptr<NPC> npc_1, const std::shared_ptr<NPC> npc_2, FightOutcome outcome) = 0;
};

class IDiceObserver {
public:
    virtual void on_throw_dice(const std::shared_ptr<NPC> npc, const std::string& value_name, const char value) const = 0;
};
