#include "../../include/npc/NPC.hpp"

#include "../../include/application/AppLogic.hpp"
#include "../../include/application/App.hpp"


#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <shared_mutex>
#include <random>
#include <string>

NPC::NPC(NPC_Type type, long pos_X, long pos_Y) 
    : type_(type),
      x_(pos_X),
      y_(pos_Y),
      move_distance_(0),
      fight_distance_(0) {
}

NPC::NPC(NPC_Type type, std::istream& input) 
    : type_(type),
      move_distance_(0), 
      fight_distance_(0) {
    input >> this->x_ >> this->y_;
}

bool NPC::is_close(std::shared_ptr<NPC> other) const {
    return std::pow(this->x_ - other->x_, 2)
           +
           std::pow(this->y_ - other->y_, 2)
           <=
           std::pow(this->fight_distance_, 2);
}

void NPC::kill() {
    std::lock_guard lock(this->mutex_);

    this->isDead_ = true;
}

bool NPC::is_dead() const {
    std::shared_lock lock(this->mutex_);
    return this->isDead_;
}

void NPC::notify(const std::shared_ptr<NPC> defender, FightOutcome outcome) {
    std::lock_guard lock(this->mutex_);

    for (auto obs : this->fight_observers_) {
        obs->on_fight(shared_from_this(), defender, outcome);
    }
}

void NPC::notify(const std::string& dice_value_name, char dice_value) {
    std::lock_guard lock(this->mutex_);

    for (auto obs : this->dice_observers_) {
        obs->on_throw_dice(shared_from_this(), dice_value_name, dice_value);
    }
}

void NPC::subscribe(const std::shared_ptr<IFightObserver> observer) {
    std::lock_guard lock(this->mutex_);

    this->fight_observers_.push_back(observer);
}

void NPC::subscribe(const std::shared_ptr<IDiceObserver> observer) {
    std::lock_guard lock(this->mutex_);

    this->dice_observers_.push_back(observer);
}

void NPC::save(std::ostream& output) const {
    output << (int)type_ << ' ' << x_ << ' ' << y_;
}

std::pair<long, long> NPC::get_position() const {
    std::shared_lock lock(this->mutex_);
    return { this->x_, this->y_ };
}

long NPC::get_move_distance() const {
    std::shared_lock lock(this->mutex_);
    return this->move_distance_;
}

long NPC::get_fight_distance() const {
    std::shared_lock lock(this->mutex_);
    return this->fight_distance_;
}

void NPC::move(long shift_X, long shift_Y) {
    std::lock_guard lock(this->mutex_);

    this->x_ = std::clamp(this->x_ + shift_X, 0l, App::getInstance().get_map_width() - 1);
    this->y_ = std::clamp(this->y_ + shift_Y, 0l, App::getInstance().get_map_height() - 1);
}

char NPC::get_symbol() const {
    std::shared_lock lock(this->mutex_);
    return this->symbol_;
}
 
std::ostream& operator<<(std::ostream& output, NPC& npc) {
    output << npc.info();

    return output;
}