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

        virtual FightOutcome fight(std::shared_ptr<class WanderingKnight>) = 0;
        virtual FightOutcome fight(std::shared_ptr<class Princess>) = 0;
        virtual FightOutcome fight(std::shared_ptr<class Dragon>) = 0;

        virtual FightOutcome accept(std::shared_ptr<NPC>) = 0;
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

        std::pair<long, long> get_position() const;

        virtual void move(long shift_X, long shift_Y, long max_X, long max_Y);
};