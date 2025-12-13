#pragma once

#include <cstddef>
#include <istream>
#include <memory>
#include <mutex>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "Interfaces.hpp"
#include "../observers/Observer.hpp"

enum struct NPC_Type {
    Dragon,
    Princess,
    WanderingKnight,

    First=Dragon,
    Last=WanderingKnight
};

enum struct FightOutcome {
    Draw,
    Defeat,
    MutualDefeat,
    Victory
};

class Dragon;
class Princess;
class WanderingKnight;

class NPC : 
    public IMortal,
    public IFightable,
    public IPrintable,
    public IMovable,
    public std::enable_shared_from_this<NPC> {
protected:
    bool isDead_ = false;
    long x_ = 0, y_ = 0;

    const size_t move_distance_;
    const size_t fight_distance_;

    NPC_Type type_;

    std::vector<std::shared_ptr<IFightObserver>> observers_;
    std::mutex mutex_;

public:
    NPC(NPC_Type type, long coord_x, long coord_y);
    NPC(NPC_Type type, std::istream& input);

    virtual FightOutcome fight(std::shared_ptr<NPC> defender);

    virtual void kill();
    virtual bool is_dead() const;

    virtual bool is_close(std::shared_ptr<NPC> other) const;

    virtual void subscribe(const std::shared_ptr<IFightObserver> observer);
    virtual void notify(const std::shared_ptr<NPC> other, FightOutcome outcome);

    virtual std::pair<long, long> get_position() const;
    virtual void move(long shift_X, long shift_Y, long max_X, long max_Y);

    virtual void save(std::ostream& out) const;
    virtual std::string info() const = 0;
    virtual void print() const = 0;

    friend std::ostream& operator<<(std::ostream& out, NPC& npc_object);
};