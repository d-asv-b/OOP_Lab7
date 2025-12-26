#pragma once

#include "IObservers.hpp"
#include <sstream>

class DiceTextObserver : public IDiceObserver {
private:
    DiceTextObserver() = default;
public:
    static std::shared_ptr<IDiceObserver> get();

    virtual void on_throw_dice(const std::shared_ptr<NPC> npc, const std::string& value_name, const char value) const override final;
};
