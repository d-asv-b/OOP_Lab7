#include "../../include/application/CommandProcessor.hpp"

CommandProcessor::CommandProcessor(size_t characters, long map_width, long map_height)
    : characters_(characters),
      mapWidth_(map_width),
      mapHeight_(map_height) {
}

bool CommandProcessor::executeCommand(const Action action, AppState& state) {
    switch (action) {
        case Action::Exit:
            return false;

        case Action::GenerateRandom:
            executeGenerate(state);
            break;

        case Action::LoadFromFile:
            executeLoad(state);
            break;

        case Action::SaveToFile:
            executeSave(state);
            break;

        case Action::StartSimulation:
            executeSimulation(state);
            break;

        default:
            return true;
    }
    return true;
}

void CommandProcessor::executeGenerate(AppState& state) {
    auto characters = genRandomNPCs(characters_, mapWidth_, mapHeight_);
    state.setCharacters(characters);
}

void CommandProcessor::executeLoad(AppState& state) {
    auto characters = loadFromFileLogic(characters_);
    state.setCharacters(characters);
}

void CommandProcessor::executeSave(const AppState& state) {
    saveToFileLogic(state.getCharacters(), characters_);
}

void CommandProcessor::executeSimulation(AppState& state) {
    if (state.hasCharacters()) {
        simulationLogic(state.getCharacters(), characters_);
    } else {
        std::cout << "\tОшибка: нет загруженных персонажей для симуляции!\n";
    }
}
