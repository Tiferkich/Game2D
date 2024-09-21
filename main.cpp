#include <iostream>
#include "Unit/Unit.h"
#include "Unit/Enemy/Enemy.h"
#include "Unit/Enemy/Golem/Golem.h"
#include "Unit/Enemy/LivingEnemy/LivingEnemy.h"
#include "Unit/Enemy/Undead/Undead.h"
#include "Unit/Enemy/Summoner/LivingSummoner.h"
#include "Unit/Enemy/Summoner/UndeadSummoner.h"
#include "Matrix/Matrix.h"
#include "Dungeon/Dungeon.h"
#include "Unit/Character/Skills/Curse/Curse.h"
#include "Unit/Character/Skills/Desiccation/Desiccation.h"
#include "Unit/Character/Skills/Necromancy/Necromancy.h"
#include "Unit/Character/Skills/Morphism/Morphism.h"


int main() {
    std::list<std::pair<Enemy *, Ceil *>> listEnemies;
    Matrix<Ceil> matrix(10, 10);
    for (auto &item: matrix) {
        item = Ceil::floor;
    }
    //std::cout << matrix.cols() << std::endl;
    TableSkills tableSkills;
    Character character(10, {10, 15}, {0, 0}, &tableSkills);
    Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[1][1]});
    Enemy enemy(Faction::undead, 10, {10, 20}, {10, 10}, "test", 100, 100, Status::wandering, 10);
//    Unit *unit = &enemy;
//    Enemy *enemy1;
//    Unit *unit;
//    std::pair<int, int> coord(10, 10);
    Golem golem(10, {9, 18}, {3, 3}, 10, 25, Ceil::essence);
    LivingEnemy knight(10, {10, 20}, {1, 0}, "livingEnemy", 100, 100);
    LivingEnemy knight2(10, {10, 20}, {5, 5}, "livingEnemy", 100, 100);

    Ceil *ceil = &dungeon.getMapLevel()[1][1];
    dungeon += {&golem, &dungeon.getMapLevel()[golem.getCoords().second][golem.getCoords().first]};
    dungeon += {&knight, &dungeon.getMapLevel()[knight.getCoords().second][knight.getCoords().first]};
    dungeon += {&knight2, &dungeon.getMapLevel()[knight2.getCoords().second][knight2.getCoords().first]};

//    knight.die();


    //my_function(&knight,dungeon);
    LivingSummoner summoner(10, {10, 10}, {1, 1}, 100);
    UndeadSummoner undeadSummoner(10, {10, 10}, {3, 2}, 100, 100);
    dungeon += {&undeadSummoner, &dungeon.getMapLevel()[summoner.getCoords().second][summoner.getCoords().first]};
    dungeon += {&summoner, &dungeon.getMapLevel()[1][1]};
    Curse curse(10);
    Desiccation desiccation;
    Necromancy necromancy(10);
    Morphism morphism(10);
    character.getDamage(50);
    character.getCharacteristics().setCurMana(10000);
    character.getTableSkills().addSkill(&curse, "Curse");
    character.getTableSkills().addSkill(&desiccation, "desiccation");
    character.getTableSkills().addSkill(&necromancy, "Necromancy");
    character.getTableSkills().addSkill(&morphism, "Morphism");
    character.getTableSkills().upgradeSkill("desiccation");
    character.getTableSkills().upgradeSkill("Curse");
    character.getTableSkills().upgradeSkill("Necromancy");
    character.getTableSkills().upgradeSkill("Morphism");
//    dungeon.printEnemies();
    summoner.die();
    knight.die();
    character.setCountEssence(10000);
    character.openEnemy(dungeon);
    character.openEnemy(dungeon);
    int mas[1] = {2};
    character.useSkill("Morphism", dungeon, mas);
    character.useSkill("Curse", dungeon);
    character.useSkill("desiccation", dungeon);
    character.useSkill("Necromancy", dungeon);
    character.useSkill("BOD", dungeon);
    dungeon.printEnemies();


    Enemy *example = &summoner;


    //summoner.becomeUndead(dungeon);
    dungeon.print();
    dungeon.allDoSomething();
    dungeon.allDoSomething();


    dungeon.print();
    dungeon.printEnemies();



    return 0;
}
