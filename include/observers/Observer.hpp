#pragma once

#include <fstream>
#include <memory>

class NPC;
enum struct FightOutcome : int;

class IFightObserver {
public:
    virtual void on_fight(const std::shared_ptr<NPC> npc_1, const std::shared_ptr<NPC> npc_2, FightOutcome outcome) = 0;
};

class TextObserver : public IFightObserver {
private:
    TextObserver() = default;
public:
    static std::shared_ptr<IFightObserver> get();

    virtual void on_fight(const std::shared_ptr<NPC> npc_1, const std::shared_ptr<NPC> npc_2, FightOutcome outcome) override;
};

class FileObserver : public IFightObserver {
private:
    std::ofstream out;
    FileObserver() = default;
public:
    ~FileObserver();

    static std::shared_ptr<IFightObserver> get();

    virtual void on_fight(const std::shared_ptr<NPC> npc_1, const std::shared_ptr<NPC> npc_2, FightOutcome outcome) override;
};
