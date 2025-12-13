#include "../../include/factories/NPCFactory.hpp"

#include "../../include/npc/Dragon.hpp"
#include "../../include/npc/Princess.hpp"
#include "../../include/npc/WanderingKnight.hpp"

#include <cstdlib>
#include <iostream>
#include <istream>
#include <memory>

std::shared_ptr<NPC> NPCFactory::createNPC(std::istream& input) {
    int type;
    std::shared_ptr<NPC> result;

    if (input >> type) {
        switch ((NPC_Type)type) {
            case NPC_Type::Dragon: {
                result = std::make_shared<Dragon>(input);
                break;
            }
            case NPC_Type::Princess: {
                result = std::make_shared<Princess>(input);
                break;
            }
            case NPC_Type::WanderingKnight: {
                result = std::make_shared<WanderingKnight>(input);
                break;
            }
            default: {
                std::cerr << "Incorrect NPC type number: " << type << std::endl;
                exit(EXIT_FAILURE);
            }
        }   
    }
    else {
        std::cerr << "No input." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (result) {
        result->subscribe(TextObserver::get());
    }

    return result;
}

std::shared_ptr<NPC> NPCFactory::createNPC(NPC_Type type, long position_X, long position_Y) {
    std::shared_ptr<NPC> result;

    switch (type) {
        case NPC_Type::Dragon: {
            result = std::make_shared<Dragon>(position_X, position_Y);
            break;
        }
        case NPC_Type::Princess: {
            result = std::make_shared<Princess>(position_X, position_Y);
            break;
        }
        case NPC_Type::WanderingKnight: {
            result = std::make_shared<WanderingKnight>(position_X, position_Y);
            break;
        }
        default: {
            std::cerr << "Incorrect NPC type number: " << (int)type << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    if (result) {
        result->subscribe(TextObserver::get());
    }
    
    return result;
}