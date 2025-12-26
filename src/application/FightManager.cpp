#include "../../include/application/FightManager.hpp"
#include <mutex>

FightManager& FightManager::get() {
    static FightManager instance;
    return instance;
}

void FightManager::add_event(FightEvent evt) {
    std::lock_guard lock(this->queue_mtx_);
    this->events_.push(evt);
}

FightEvent FightManager::get_event() {
    std::lock_guard lock(this->queue_mtx_);
    FightEvent evt = this->events_.front();
    this->events_.pop();

    return evt;
}

bool FightManager::has_events() const {
    std::lock_guard lock(this->queue_mtx_);
    return !this->events_.empty();
}
