#include "../../include/application/App.hpp"

#include "../../include/application/UserInteractionHandler.hpp"
#include "../../include/application/CommandProcessor.hpp"
#include "../../include/application/AppState.hpp"
#include "../../include/application/PrintHandler.hpp"

#include <cmath>
#include <cstddef>
#include <memory>
#include <shared_mutex>
#include <sstream>
#include <string>

std::unique_ptr<App> App::instance_ = nullptr;
std::mutex App::instance_mtx_;

App::App(size_t characters, long map_width, long map_height)
    : charactersCount_(characters),
      mapWidth_(std::abs(map_width)),
      mapHeight_(std::abs(map_height)),
      map_(mapHeight_, std::vector<char>(mapWidth_, '.'))
      {
}

App& App::getInstance(size_t characters, long map_width, long map_height) {
    std::lock_guard lock(instance_mtx_);

    if (instance_ == nullptr) {
        instance_ = std::unique_ptr<App>(new App(characters, map_width, map_height));
    }

    return *instance_;
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

void App::edit_map(long posX, long posY, char newVal) {
    std::lock_guard lock(this->map_mtx_);
    (this->map_)[posY][posX] = newVal;
}

void App::print_map() const {
    std::stringstream ss;


    for (long i = 0; i < mapWidth_ + 2; ++i) {
        ss << "-";
    }

    ss << "\n";
    {
        std::shared_lock lock(this->map_mtx_);
        for (long i = 0; i < mapHeight_; ++i) {
            ss << "|";
            
            for (long j = 0; j < mapWidth_; ++j) {
                ss << this->map_[i][j];
            }

            ss << "|\n";
        }
    }

    for (long i = 0; i < mapWidth_ + 2; ++i) {
        ss << "-";
    }

    ss << "\n\n";

    PrintHandler::print(ss);
}

long App::get_map_width() const {
    std::shared_lock lock(this->map_mtx_);
    return this->mapWidth_;
}

long App::get_map_height() const {
    std::shared_lock lock(this->map_mtx_);
    return this->mapHeight_;
}

char App::get_map_state(long posX, long posY) const {
    std::shared_lock lock(this->map_mtx_);
    return (this->map_)[posY][posX];
}