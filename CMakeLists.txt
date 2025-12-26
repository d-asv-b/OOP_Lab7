cmake_minimum_required(VERSION 3.10)

project(Lab7)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME}_lib
  src/application/App.cpp
  src/npc/NPC.cpp
  src/factories/NPCFactory.cpp
  src/observers/FightTextObserver.cpp
  src/observers/FightFileObserver.cpp
  src/observers/DiceTextObserver.cpp
  src/application/AppLogic.cpp
  src/npc/Dragon.cpp
  src/npc/Princess.cpp
  src/npc/WanderingKnight.cpp
  src/application/AppState.cpp
  src/application/UserInteractionHandler.cpp
  src/application/CommandProcessor.cpp
  src/application/FightManager.cpp
)

add_executable(
    ${PROJECT_NAME}_exe main.cpp
)
set_target_properties(${PROJECT_NAME}_exe PROPERTIES OUTPUT_NAME "Lab_exe")

target_compile_options(${PROJECT_NAME}_exe PRIVATE -g)
target_include_directories(${PROJECT_NAME}_exe PUBLIC include)
target_link_libraries(${PROJECT_NAME}_exe PRIVATE ${PROJECT_NAME}_lib)

enable_testing()

# NPCFactory Tests
add_executable(NPCFactory_tests_lab7 test/test_npc_factory.cpp)
target_include_directories(NPCFactory_tests_lab7 PUBLIC include)
target_link_libraries(NPCFactory_tests_lab7 PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME NPCFactory COMMAND NPCFactory_tests_lab7)

# AppState Tests
add_executable(AppState_tests_lab7 test/test_app_state.cpp)
target_include_directories(AppState_tests_lab7 PUBLIC include)
target_link_libraries(AppState_tests_lab7 PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME AppState COMMAND AppState_tests_lab7)

# NPC Base Tests
add_executable(NPCBase_tests_lab7 test/test_npc_base.cpp)
target_include_directories(NPCBase_tests_lab7 PUBLIC include)
target_link_libraries(NPCBase_tests_lab7 PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME NPCBase COMMAND NPCBase_tests_lab7)

# NPC Concrete Tests
add_executable(NPCConcrete_tests_lab7 test/test_npc_concrete.cpp)
target_include_directories(NPCConcrete_tests_lab7 PUBLIC include)
target_link_libraries(NPCConcrete_tests_lab7 PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME NPCConcrete COMMAND NPCConcrete_tests_lab7)

# FightManager Tests
add_executable(FightManager_tests_lab7 test/test_fight_manager.cpp)
target_include_directories(FightManager_tests_lab7 PUBLIC include)
target_link_libraries(FightManager_tests_lab7 PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME FightManager COMMAND FightManager_tests_lab7)

# Observers Tests
add_executable(Observers_tests_lab7 test/test_observers.cpp)
target_include_directories(Observers_tests_lab7 PUBLIC include)
target_link_libraries(Observers_tests_lab7 PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME Observers COMMAND Observers_tests_lab7)
