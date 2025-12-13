#pragma once

#include <cstddef>
#include "AppLogic.hpp"
#include "AppState.hpp"

enum struct Action;

class CommandProcessor {
private:
    size_t characters_;
    long mapWidth_, mapHeight_;

public:
    CommandProcessor(size_t characters, long map_width, long map_height);

    bool executeCommand(const Action action, AppState& state);

private:
    void executeGenerate(AppState& state);
    void executeLoad(AppState& state);
    void executeSave(const AppState& state);
    void executeSimulation(AppState& state);
};
