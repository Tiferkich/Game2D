//
// Created by sakhd on 23.10.2023.
//

#include "LivingEnemy.h"
#include "../../../Dungeon/Dungeon.h"
#include "../Undead/Undead.h"

void LivingEnemy::becomeUndead(Dungeon &dungeon) {
    if (status != Status::dead) return;
    faction = Faction::undead;
    dungeon.getListEnemies().push_back(
            {new Undead(10, {damage.first, damage.second}, {coords.first, coords.second}, "undead",
                        "livingEnemy",
                        maxHP, maxHP), &(dungeon.getMapLevel()[coords.first][coords.second])});
    (--dungeon.getListEnemies().end())->first->setHeap(true);
    (--dungeon.getListEnemies().end())->first->setFaction(Faction::character);
    this->methodAfterDie(dungeon);
}

void LivingEnemy::methodAfterDie(Dungeon &dungeon) {
    if (status == Status::dead && (faction == Faction::character || faction == Faction::undead)) {
        for (auto i = dungeon.getListEnemies().begin(); i != dungeon.getListEnemies().end(); i++) {
            if (i->first == this) {
//                if (i->first->isHeap()) delete i->first;
                dungeon.getListEnemies().erase(i);
                break;
            }
        }
    }
}
