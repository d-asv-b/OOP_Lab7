#include "include/application/App.hpp"

// Количество NPC
#define CHARACTER_COUNT 50

// Размеры карты
#define MAP_WIDTH 100
#define MAP_HEIGHT 20

int main() {
    App::getInstance(CHARACTER_COUNT, MAP_WIDTH, MAP_HEIGHT).run();

    return 0;
}
