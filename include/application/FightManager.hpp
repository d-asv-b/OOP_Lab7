#pragma once

#include "../npc/NPC.hpp"

#include <memory>
#include <mutex>
#include <queue>

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};


class FightManager {
private:
    std::queue<FightEvent> events_;
    mutable std::mutex queue_mtx_;

    FightManager() = default;

public:
    static FightManager& get();

    void add_event(FightEvent evt);
    FightEvent get_event();
    bool has_events() const;
};
