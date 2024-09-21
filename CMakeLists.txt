cmake_minimum_required(VERSION 3.22.1)
project(gameLab3)


set(CMAKE_CXX_STANDARD 20)


add_library(Enemy Unit/Enemy/Enemy.cpp Unit/Enemy/Enemy.h)


add_library(Golem Unit/Enemy/Golem/Golem.cpp Unit/Enemy/Golem/Golem.h)
target_link_libraries(Golem Enemy)


add_library(LivingEnemy Unit/Enemy/LivingEnemy/LivingEnemy.cpp Unit/Enemy/LivingEnemy/LivingEnemy.h)
target_link_libraries(LivingEnemy Enemy)


add_library(Undead Unit/Enemy/Undead/Undead.cpp Unit/Enemy/Undead/Undead.h)
target_link_libraries(Undead Enemy)

add_library(LivingSummoner Unit/Enemy/Summoner/LivingSummoner.cpp Unit/Enemy/Summoner/LivingSummoner.h)
add_library(UndeadSummoner Unit/Enemy/Summoner/UndeadSummoner.cpp Unit/Enemy/Summoner/UndeadSummoner.cpp)
target_link_libraries(LivingSummoner Enemy)
target_link_libraries(UndeadSummoner Enemy)

add_library(Character Unit/Character/Character.cpp Unit/Character/Character.h Unit/Character/TableSkills.h Unit/Character/Skills/Skills.h)
target_link_libraries(Character Enemy UndeadSummoner)


add_library(Dungeon Dungeon/Dungeon.cpp Dungeon/Dungeon.h)
target_link_libraries(Dungeon Golem Enemy Character)


#TODO Добавить подключение game

add_library(Game Game/Game.cpp Game/Game.h)

target_link_libraries(Game Dungeon Character Undead LivingEnemy LivingSummoner UndeadSummoner Golem)

add_subdirectory(Tests)

add_executable(gameLab3 main.cpp)

target_link_libraries(gameLab3 Enemy Dungeon Golem Character LivingEnemy LivingSummoner UndeadSummoner Enemy Game)


add_subdirectory(gameSfml)