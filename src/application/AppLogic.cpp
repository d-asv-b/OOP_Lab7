#include "../../include/application/AppLogic.hpp"
#include <algorithm>
#include <cstddef>
#include <memory>

void printGreeting() {
    std::cout << "-------------------------------------------------------------------------\n" <<
                 "|                                                                       |\n" <<
                 "|                          Игра Baldur's Fate 3                         |\n" <<
                 "|                                                                       |\n" <<
                 "-------------------------------------------------------------------------\n\n";
                 
    std::cout << "========        Пожалуйста, выберите действие из списка:         ========\n" <<
                 "\t1) Сгенерировать случайных NPC;\n" <<
                 "\t2) Загрузить данные из файла;\n" <<
                 "\t3) Сохранить данные в файл;\n" <<
                 "\t4) Запустить симуляцию;\n" <<
                 "\t0) Выйти из симулятора.\n\n" <<
                 "\tВаш выбор: ";
}

std::string validPathInputLogic(Action action) {
    std::string path;
                
    std::cout << "\tПожалуйста, введите путь к файлу:\n\t\t";
    std::cin >> path;

    if (action == Action::SaveToFile && !std::filesystem::exists(path)) {
        return path;
    }

    while (!std::filesystem::is_regular_file(path)) {
        std::cout << "\tПуть указывает не на файл!\n";
        std::cout << "\tПожалуйста, введите путь к файлу:\n\t\t";
        std::cin >> path;
    }

    return path;
}

std::vector<std::shared_ptr<NPC>> genRandomNPCs(const size_t characters, const long mapWidth, const long mapHeight) {
    std::vector<std::shared_ptr<NPC>> result;

    std::random_device rnd;
    std::mt19937 generator(rnd());

    std::uniform_int_distribution<> npc_type_distr((int)NPC_Type::First, (int)NPC_Type::Last);
    std::uniform_int_distribution<> coord_distrib_x(0, mapWidth);
    std::uniform_int_distribution<> coord_distrib_y(0, mapHeight);

    NPCFactory factory;

    std::cout << "\tНачинаем генерацию " << characters << " NPC...\n";

    for (size_t i = 0; i < characters; ++i) {
        std::shared_ptr<NPC> newNPC = factory.createNPC(
            (NPC_Type)npc_type_distr(generator),
            (long)coord_distrib_x(generator),
            (long)coord_distrib_y(generator)
        );

        std::cout << "\t\t";
        newNPC->print();

        result.push_back(newNPC);
    }

    std::cout << "\tNPC успешно сгенерированы!\n";

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

        std::cout << "\tЗагружаем " << count << " NPC из файла...\n";

        for (size_t i = 0; i < count && i < characters; ++i) {
            std::shared_ptr<NPC> newNPC = factory.createNPC(in);

            std::cout << "\t\t";
            newNPC->print();

            loadedCharacters.push_back(newNPC);
        }

        in.close();

        std::cout << "\tNPC загружены!\n";
    }

    return loadedCharacters;
}

void saveToFileLogic(const std::vector<std::shared_ptr<NPC>> characters, const size_t charactersCount) {
    std::string outputFilePath = validPathInputLogic(Action::SaveToFile);

    std::ofstream out;
    out.open(outputFilePath, std::ofstream::out | std::ofstream::trunc);

    if (out.is_open()) {
        size_t count = characters.size();
        std::cout << "\tСохраняем " << count << " NPC в файл...\n";

        out << count << "\n";

        for (size_t i = 0; i < count && i < charactersCount; ++i) {
            characters[i]->save(out);
            out << "\n";
        }

        out.close();

        std::cout << "\tNPC сохранены!\n";
    }
}

void simulationLogic(const std::vector<std::shared_ptr<NPC>> characters, const size_t charactersCount) {
    std::cout << "\tНачинаем симуляцию...\n";

    for (size_t i = 0; i < characters.size() - 1; ++i) {
        for (size_t j = i + 1; j < characters.size() && !characters[i]->is_dead(); ++j) {
            if (
                characters[i]->is_close(characters[j]) && 
                !characters[j]->is_dead()
            ) {
                FightOutcome fightResult = characters[i]->fight(characters[j]);
                characters[i]->notify(characters[j], fightResult);
            }
        }
    }

    std::cout << "\tСимуляция закончена. В живых осталось ";
    std::cout << std::count_if(
        characters.begin(),
        characters.end(),
        [](std::shared_ptr<NPC> npc) {
            return !npc->is_dead();
        }
    );
    std::cout << " NPC.\n";
}