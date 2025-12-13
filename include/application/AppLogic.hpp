#pragma once

#include "../factories/NPCFactory.hpp"

#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
#include <random>
#include <filesystem>
#include <algorithm>

enum struct Action {
    Exit,
    GenerateRandom,
    LoadFromFile,
    SaveToFile,
    StartSimulation
};

void printGreeting();

std::string validPathInputLogic(Action);

std::vector<std::shared_ptr<NPC>> genRandomNPCs(const size_t characters, const long map_width, const long map_height);

std::vector<std::shared_ptr<NPC>> loadFromFileLogic(const size_t characters);

void saveToFileLogic(const std::vector<std::shared_ptr<NPC>> characters, const size_t charactersCount);

void simulationLogic(const std::vector<std::shared_ptr<NPC>> characters, const size_t charactersCount);