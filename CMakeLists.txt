cmake_minimum_required(VERSION 3.10)

project(Lab6)

set(CMAKE_BUILD_TYPE Debug)

add_library(${PROJECT_NAME}_lib
  src/App.cpp
  src/NPC.cpp
  src/NPCFactory.cpp
  src/Observer.cpp
  src/AppLogic.cpp
  src/Dragon.cpp
  src/Princess.cpp
  src/WanderingKnight.cpp
  src/AppState.cpp
  src/UserInteractionHandler.cpp
  src/CommandProcessor.cpp
)

add_executable(
    ${PROJECT_NAME}_exe main.cpp
)
set_target_properties(${PROJECT_NAME}_exe PROPERTIES OUTPUT_NAME "Lab_exe")

target_compile_options(${PROJECT_NAME}_exe PRIVATE -g)
target_include_directories(${PROJECT_NAME}_exe PUBLIC include)
target_link_libraries(${PROJECT_NAME}_exe PRIVATE ${PROJECT_NAME}_lib)

enable_testing()

# Dragon Tests
add_executable(Dragon_tests test/test_dragon.cpp)
target_include_directories(Dragon_tests PUBLIC include)
target_link_libraries(Dragon_tests PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME Dragon COMMAND Dragon_tests)

# Princess Tests
add_executable(Princess_tests test/test_princess.cpp)
target_include_directories(Princess_tests PUBLIC include)
target_link_libraries(Princess_tests PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME Princess COMMAND Princess_tests)

# WanderingKnight Tests
add_executable(WanderingKnight_tests test/test_wandering_knight.cpp)
target_include_directories(WanderingKnight_tests PUBLIC include)
target_link_libraries(WanderingKnight_tests PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME WanderingKnight COMMAND WanderingKnight_tests)

# NPCFactory Tests
add_executable(NPCFactory_tests test/test_npc_factory.cpp)
target_include_directories(NPCFactory_tests PUBLIC include)
target_link_libraries(NPCFactory_tests PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME NPCFactory COMMAND NPCFactory_tests)

# AppState Tests
add_executable(AppState_tests test/test_app_state.cpp)
target_include_directories(AppState_tests PUBLIC include)
target_link_libraries(AppState_tests PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME AppState COMMAND AppState_tests)

# Fight Logic Tests
add_executable(FightLogic_tests test/test_fight_logic.cpp)
target_include_directories(FightLogic_tests PUBLIC include)
target_link_libraries(FightLogic_tests PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME FightLogic COMMAND FightLogic_tests)