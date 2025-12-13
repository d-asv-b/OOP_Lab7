#pragma once

#include "AppLogic.hpp"

#include <iostream>
#include <mutex>

class UserInteractionHandler {
private:
    std::mutex printMutex_;
public:
    UserInteractionHandler() = default;

    void showGreeting() const;
    Action getUserChoice();
    void showInvalidChoice() const;
    void showContinuePrompt();
    void showExitMessage() const;
    
private:
    void clearScreen() const;
};
