//
// Created by sakhd on 23.10.2023.
//

#include "Game.h"


std::vector<std::string> Game::allTypesEnemies = {"livingEnemy", "livingSummoner", "undead", "undeadSummoner", "golem"};

std::vector<std::string> Game::allSkills = {"Curse", "Desiccation", "Morphism", "Necromancy"};

int Game::option[12][2] = {{1,  0},
                           {2,  0},
                           {3,  0},
                           {4,  0},
                           {5,  0},
                           {6,  0},
                           {7,  0},
                           {8,  0},
                           {9,  0},
                           {10, 0},
                           {11, 0},
                           {12, 0}};

///TODO std::array
int Game::makeTick(int options[]) {

    hero.doSomething(options, *this);
//    allMap[this->curLvl].allDoSomething();

    return 0;
}


Character &Game::getHero() {
    return hero;
}

std::vector<Dungeon> &Game::getAllMap() {
    return allMap;
}

unsigned int Game::getCurLvl() {
    return curLvl;
}


const TableSkills &Game::getTableSkills() const {
    return tableSkills;
}

void Game::setHero(const Character &hero) {
    Game::hero = hero;
}


void Game::setCurLvl(unsigned int curLvl) {
    Game::curLvl = curLvl;
}


void Game::setTableSkills(const TableSkills &tableSkills) {
    Game::tableSkills = tableSkills;
}

void Game::setAllMap(const std::vector<Dungeon> &allMap) {
    Game::allMap = allMap;
}

unsigned int Game::getMaxLvl() const {
    return maxLvl;
}

void Game::setAllTypesEnemies(const std::vector<std::string> &allTypesEnemies) {
    Game::allTypesEnemies = allTypesEnemies;
}

void Game::setAllSkills(const std::vector<std::string> &allSkills) {
    Game::allSkills = allSkills;
}

void Game::setMaxLvl(unsigned int maxLvl) {
    Game::maxLvl = maxLvl;
}
