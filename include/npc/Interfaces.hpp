#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <utility>

class NPC;
enum struct FightOutcome;

class IPrintable {
    public:
        virtual ~IPrintable() = default;

        virtual void print() const = 0;
        virtual std::string info() const = 0;
};

class IFightable {
    public:
        virtual ~IFightable() = default;

        virtual FightOutcome fight(std::shared_ptr<class WanderingKnight> defender) = 0;
        virtual FightOutcome fight(std::shared_ptr<class Princess> defender) = 0;
        virtual FightOutcome fight(std::shared_ptr<class Dragon> defender) = 0;

        virtual FightOutcome accept(std::shared_ptr<NPC> attacker) = 0;

        virtual long get_fight_distance() const = 0;
};

class IMortal {
    public:
        virtual ~IMortal() = default;

        virtual void kill() = 0;
        virtual bool is_dead() const = 0;
};

class IMovable {
    public:
        ~IMovable() = default;

        virtual std::pair<long, long> get_position() const = 0;

        virtual void move(long shift_X, long shift_Y) = 0;
        virtual long get_move_distance() const = 0;
};