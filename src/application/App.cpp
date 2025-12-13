#include "../../include/application/App.hpp"

#include "../../include/application/UserInteractionHandler.hpp"
#include "../../include/application/CommandProcessor.hpp"
#include "../../include/application/AppState.hpp"

#include <cmath>

App::App(size_t characters, long map_width, long map_height)
    : charactersCount_(characters),
      mapWidth_(std::abs(map_width)),
      mapHeight_(std::abs(map_width)) {
}

void App::run() const {
    AppState state;
    UserInteractionHandler interactionHandler;
    CommandProcessor processor(this->charactersCount_, this->mapWidth_, this->mapHeight_);

    while (true) {
        interactionHandler.showGreeting();

        Action choice = interactionHandler.getUserChoice();
        bool shouldContinue = processor.executeCommand(choice, state);

        if (choice == Action::Exit) {
            interactionHandler.showExitMessage();
            break;
        } else if (choice < Action::GenerateRandom || choice > Action::StartSimulation) {
            interactionHandler.showInvalidChoice();
        }

        interactionHandler.showContinuePrompt();
    }
}