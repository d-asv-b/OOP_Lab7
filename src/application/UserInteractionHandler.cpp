#include "../../include/application/UserInteractionHandler.hpp"

void UserInteractionHandler::showGreeting() const {
    printGreeting();
}

Action UserInteractionHandler::getUserChoice() {
    int choice;
    std::cin >> choice;
    std::cout << "\n";
    return (Action)choice;
}

void UserInteractionHandler::showInvalidChoice() const {
    std::cout << "\tТакой команды не существует! Пожалуйства, введите снова.\n\n";
}

void UserInteractionHandler::showContinuePrompt() {
    std::cout << "\n\tНажмите Enter для продолжения...";
    std::cin.ignore(1'000'000, '\n');
    std::cin.get();
    clearScreen();
}

void UserInteractionHandler::showExitMessage() const {
    std::cout << "Завершаем работу...\n";
}

void UserInteractionHandler::clearScreen() const {
    std::cout << "\e[1;1H\e[2J"
              << "\n";
}
