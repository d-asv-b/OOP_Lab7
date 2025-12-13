#include "include/application/App.hpp"

#include <memory>

// Количество NPC
#define CHARACTER_COUNT 50

// Размеры карты
#define MAP_WIDTH 100
#define MAP_HEIGHT 100

int main() {
    auto appInstance = std::make_unique<App>(
        CHARACTER_COUNT,
        MAP_WIDTH,
        MAP_HEIGHT
    );
    appInstance->run();

    return 0;
}
