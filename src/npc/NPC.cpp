#include "../../include/npc/NPC.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <mutex>
#include <random>

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
    std::lock_guard<std::mutex> lock(this->mutex_);

    this->isDead_ = true;
}

bool NPC::is_dead() const { 
    return this->isDead_;
}

FightOutcome NPC::fight(std::shared_ptr<NPC> defender) {
    std::scoped_lock lock(
        this->mutex_,
        defender->mutex_
    );

    if (!this->is_close(defender)) {
        return FightOutcome::Draw;
    }

    if (defender->is_dead()) {
        return FightOutcome::Victory;
    }

    if (this->is_dead()) {
        return FightOutcome::Defeat;
    }

    FightOutcome result = FightOutcome::Draw;

    std::random_device rnd;
    std::mt19937 generator(rnd());

    std::uniform_int_distribution<int> dice_6(1, 6);

    int this_defense   = dice_6(generator);
    int this_strength  = dice_6(generator);

    int defender_defense   = dice_6(generator);
    int defender_strength  = dice_6(generator);

    if (this_strength > defender_defense) {
        defender->kill();
        result = FightOutcome::Victory;
    }

    if (this_defense < defender_strength) {
        this->kill();

        if (result == FightOutcome::Victory) {
            result = FightOutcome::MutualDefeat;
        }
        else {
            result = FightOutcome::Defeat;
        }
    }

    return result;
}

void NPC::notify(const std::shared_ptr<NPC> defender, FightOutcome outcome) {
    std::lock_guard<std::mutex> lock(this->mutex_);

    for (auto obs : this->observers_) {
        obs->on_fight(shared_from_this(), defender, outcome);
    }
}

void NPC::subscribe(const std::shared_ptr<IFightObserver> observer) {
    std::lock_guard<std::mutex> lock(this->mutex_);

    this->observers_.push_back(observer);
}

void NPC::save(std::ostream& output) const {
    output << (int)type_ << ' ' << x_ << ' ' << y_;
}

std::pair<long, long> NPC::get_position() const {
    return { this->x_, this->y_ };
}

std::ostream& operator<<(std::ostream& output, NPC& npc) {
    output << npc.info();

    return output;
}