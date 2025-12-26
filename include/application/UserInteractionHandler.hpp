#pragma once

#include "AppLogic.hpp"

#include <iostream>

class UserInteractionHandler {
private:
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
