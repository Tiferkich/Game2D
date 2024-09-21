//
// Created by sakhd on 23.10.2023.
//

#include "Golem.h"
#include "../../../Dungeon/Dungeon.h"

void Golem::getDamage(int damage) {
    srand(time(0));
    int chance = rand() % 100;
    if (chance > hitPercentage) {
        curHP -= damage;
        if (curHP <= 0) {
            die();
        }
    }
}

void Golem::methodAfterDie(Dungeon &dungeon) {
    if (status != Status::dead) return;
    if (dungeon.getMapLevel()[coords.first][coords.second] != Ceil::ladder &&
        dungeon.getMapLevel()[coords.first][coords.second] != Ceil::closeDoor &&
        dungeon.getMapLevel()[coords.first][coords.second] != Ceil::openDoor)
        dungeon.getMapLevel()[coords.first][coords.second] = ceil;
    for (auto i = dungeon.getListEnemies().begin(); i != dungeon.getListEnemies().end(); i++) {
        if (i->first == this) {
//            if (i->first->isHeap()) delete i->first;
            dungeon.getListEnemies().erase(i);
            break;
        }
    }
}
