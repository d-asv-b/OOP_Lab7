#include "../../include/application/UserInteractionHandler.hpp"
#include "../../include/application/PrintHandler.hpp"

void UserInteractionHandler::showGreeting() const {
    printGreeting();
}

Action UserInteractionHandler::getUserChoice() {
    int choice;
    std::cin >> choice;
    PrintHandler::print("\n");
    return (Action)choice;
}

void UserInteractionHandler::showInvalidChoice() const {
    PrintHandler::print("\tТакой команды не существует! Пожалуйства, введите снова.\n\n");
}

void UserInteractionHandler::showContinuePrompt() {
    PrintHandler::print("\n\tНажмите Enter для продолжения...");
    std::cin.ignore(1'000'000, '\n');
    std::cin.get();
    clearScreen();
}

void UserInteractionHandler::showExitMessage() const {
    PrintHandler::print("Завершаем работу...\n");
}

void UserInteractionHandler::clearScreen() const {
    PrintHandler::print("\e[1;1H\e[2J\n");
}
