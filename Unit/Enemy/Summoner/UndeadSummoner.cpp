//
// Created by sakhd on 26.10.2023.
//

#include "UndeadSummoner.h"

#define STEP 4

void UndeadSummoner::doSomething(Dungeon &dungeon) {
    if (status == Status::dead) {
        return;
    }

    Unit *someone = findTarget(dungeon);
    if (someone == nullptr) {
        status = Status::wandering;
        srand(time(0));
        int i = rand() % 4;
        int dx[4] = {1, 0, -1, 0};   // смещения, соответствующие соседям ячейки
        int dy[4] = {0, 1, 0, -1};
        if (coords.first + dy[i] < 0 || coords.second + dx[i] < 0 ||
            coords.second + dx[i] >= dungeon.getMapLevel().cols() ||
            coords.first + dy[i] >= dungeon.getMapLevel().rows())
            return;
        try {
            move(dungeon.getMapLevel(), {coords.first + dy[i], coords.second + dx[i]});
        } catch (...) {}
        return;
    }
    try {
        move(dungeon.getMapLevel(), {someone->getCoords().first, someone->getCoords().second});
        status = Status::aggresion;
    } catch (...) {}
    try {
        summon(dungeon, {coords.first, coords.second}, dungeon.getHero().first->getLvl() / 2, curHP,faction);
    } catch (...) {}
    try {
        attack(*someone);
        status = Status::aggresion;
    } catch (...) {}
}
