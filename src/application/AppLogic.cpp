#include "../../include/application/AppLogic.hpp"
#include "../../include/application/PrintHandler.hpp"
#include "../../include/application/FightManager.hpp"
#include "../../include/application/App.hpp"

#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <utility>

#define WITH_COROUTINES

void printGreeting() {
    PrintHandler::print("-------------------------------------------------------------------------\n"
                       "|                                                                       |\n"
                       "|                          Игра Baldur's Fate 3                         |\n"
                       "|                                                                       |\n"
                       "-------------------------------------------------------------------------\n\n");

    PrintHandler::print("========        Пожалуйста, выберите действие из списка:         ========\n"
                       "\t1) Сгенерировать случайных NPC;\n"
                       "\t2) Загрузить данные из файла;\n"
                       "\t3) Сохранить данные в файл;\n"
                       "\t4) Запустить симуляцию;\n"
                       "\t0) Выйти из симулятора.\n\n"
                       "\tВаш выбор: ");
}

std::string validPathInputLogic(Action action) {
    std::string path;
                
    PrintHandler::print("\tПожалуйста, введите путь к файлу:\n\t\t");
    std::cin >> path;

    if (action == Action::SaveToFile && !std::filesystem::exists(path)) {
        return path;
    }

    while (!std::filesystem::is_regular_file(path)) {
        PrintHandler::print("\tПуть указывает не на файл!\n");
        PrintHandler::print("\tПожалуйста, введите путь к файлу:\n\t\t");
        std::cin >> path;
    }

    return path;
}

std::vector<std::shared_ptr<NPC>> genRandomNPCs(const size_t characters, const long mapWidth, const long mapHeight) {
    std::vector<std::shared_ptr<NPC>> result;

    std::random_device rnd;
    std::mt19937 generator(rnd());

    std::uniform_int_distribution<> npc_type_distr((int)NPC_Type::First, (int)NPC_Type::Last);
    std::uniform_int_distribution<> coord_distrib_x(0, mapWidth - 1);
    std::uniform_int_distribution<> coord_distrib_y(0, mapHeight - 1);

    NPCFactory factory;

    std::stringstream ss;
    ss << "\tНачинаем генерацию " << characters << " NPC...\n";
    PrintHandler::print(ss);

    for (size_t i = 0; i < characters; ++i) {
        std::shared_ptr<NPC> newNPC = factory.createNPC(
            (NPC_Type)npc_type_distr(generator),
            (long)coord_distrib_x(generator),
            (long)coord_distrib_y(generator)
        );

        PrintHandler::print("\t\t");
        newNPC->print();

        result.push_back(newNPC);
    }

    PrintHandler::print("\tNPC успешно сгенерированы!\n");

    return result;
}

std::vector<std::shared_ptr<NPC>> loadFromFileLogic(const size_t characters) {
    std::string inputFilePath = validPathInputLogic(Action::LoadFromFile);
    std::vector<std::shared_ptr<NPC>> loadedCharacters;

    NPCFactory factory;

    std::ifstream in;
    in.open(inputFilePath);

    if (in.is_open()) {
        size_t count;
        in >> count;

        std::stringstream ss;
        ss << "\tЗагружаем " << count << " NPC из файла...\n";
        PrintHandler::print(ss);

        for (size_t i = 0; i < count && i < characters; ++i) {
            std::shared_ptr<NPC> newNPC = factory.createNPC(in);

            PrintHandler::print("\t\t");
            newNPC->print();

            loadedCharacters.push_back(newNPC);
        }

        in.close();

        PrintHandler::print("\tNPC загружены!\n");
    }

    return loadedCharacters;
}

void saveToFileLogic(const std::vector<std::shared_ptr<NPC>> characters, const size_t charactersCount) {
    std::string outputFilePath = validPathInputLogic(Action::SaveToFile);

    std::ofstream out;
    out.open(outputFilePath, std::ofstream::out | std::ofstream::trunc);

    if (out.is_open()) {
        size_t count = characters.size();
        std::stringstream ss;
        ss << "\tСохраняем " << count << " NPC в файл...\n";
        PrintHandler::print(ss);

        out << count << "\n";

        for (size_t i = 0; i < count && i < charactersCount; ++i) {
            characters[i]->save(out);
            out << "\n";
        }

        out.close();

        PrintHandler::print("\tNPC сохранены!\n");
    }
}

void simulationLogic(const std::vector<std::shared_ptr<NPC>> characters, const size_t charactersCount) {
    PrintHandler::print("\tНачинаем симуляцию...\n");

    for (const std::shared_ptr<NPC> npc : characters) {
        std::pair<long, long> pos = npc->get_position();
        App::getInstance().edit_map(pos.first, pos.second, npc->get_symbol());
    }

    bool isRunning = false;
    std::condition_variable cv;
    std::mutex mtx;
    std::unique_lock lock(mtx);

#ifndef WITH_COROUTINES
    auto moveHandler = [characters, &isRunning, &cv, &lock]() {
        while(!isRunning) {
            cv.wait(lock);
        }

        while (isRunning) {
            for (const std::shared_ptr<NPC>& npc : characters) {
                if (!npc->is_dead()) {
                    std::random_device rnd;
                    std::mt19937 generator(rnd());
    
                    std::uniform_int_distribution<long> shift(-npc->get_move_distance(), npc->get_move_distance());

                    std::pair<long, long> old_pos = npc->get_position();
                    App::getInstance().edit_map(old_pos.first, old_pos.second, '.');

                    npc->move(shift(generator), shift(generator));
                    
                    std::pair<long, long> new_pos = npc->get_position();
                    App::getInstance().edit_map(new_pos.first, new_pos.second, npc->get_symbol());

                    for (const std::shared_ptr<NPC>& other_npc : characters) {
                        if (npc != other_npc && !other_npc->is_dead() && npc->is_close(other_npc)) {
                            FightManager::get().add_event({ npc, other_npc });
                        }
                    }
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    };

    auto fightHandler = [characters, &isRunning, &cv, &lock]() {
        while(!isRunning) {
            cv.wait(lock);
        }

        while (isRunning) {
            if (FightManager::get().has_events()) {
                FightEvent event = FightManager::get().get_event();

                if (
                    !event.attacker->is_dead() && !event.defender->is_dead() &&
                    event.attacker->is_close(event.defender)
                ) {
                    FightOutcome result = event.defender->accept(event.attacker);
                    event.attacker->notify(event.defender, result);

                    if (result == FightOutcome::Victory) {
                        std::pair<long, long> pos = event.defender->get_position();
                        App::getInstance().edit_map(pos.first, pos.second, '.');
                    }
                    else if (result == FightOutcome::Defeat) {
                        std::pair<long, long> pos = event.attacker->get_position();
                        App::getInstance().edit_map(pos.first, pos.second, '.');
                    }
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    };

    std::thread moveThread(moveHandler);
    std::thread fightThread(fightHandler);

    auto start_time = std::chrono::steady_clock::now();

#elseif

#endif

    isRunning = true;
    cv.notify_all();

    while (isRunning) {
        App::getInstance().print_map();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        auto elapsed = std::chrono::steady_clock::now() - start_time;
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
        if (seconds >= 30) {
            isRunning = false;
        }
    }

    moveThread.join();
    fightThread.join();

    std::stringstream ss;
    ss << "\tСимуляция закончена. В живых осталось ";
    ss << std::count_if(
        characters.begin(),
        characters.end(),
        [](std::shared_ptr<NPC> npc) {
            return !npc->is_dead();
        }
    );
    ss << " NPC.\n";
    PrintHandler::print(ss);
}

char tossD6() {
    std::random_device rnd;
    std::mt19937 generator(rnd());

    std::uniform_int_distribution<char> dice_6(1, 6);

    return dice_6(generator);
}