#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <iostream>
#include "../Unit/Unit.h"
#include "../Unit/Enemy/Enemy.cpp"
#include "../Unit/Enemy/Golem/Golem.cpp"
#include "../Unit/Enemy/LivingEnemy/LivingEnemy.cpp"
#include "../Unit/Enemy/Undead/Undead.cpp"
#include "../Unit/Enemy/Summoner/LivingSummoner.cpp"
#include "../Unit/Enemy/Summoner/UndeadSummoner.cpp"
#include "../Unit/Character/Character.cpp"
#include "../Dungeon/Dungeon.cpp"
#include "../Unit/Character/Skills/Curse/Curse.h"
#include "../Unit/Character/Skills/Desiccation/Desiccation.h"
#include "../Unit/Character/Skills/Necromancy/Necromancy.h"
#include "../Unit/Character/Skills/Morphism/Morphism.h"


TEST_CASE("Enemies") {
    SECTION("Constructors") {
        SECTION("Gollum") {
            Golem golem(10, {10, 15}, {10, 15}, 10, 10, Ceil::essence);
            REQUIRE(golem.getSpeed() == 10);
            REQUIRE(golem.Damage().first == 10);
            REQUIRE(golem.Damage().second == 15);
            REQUIRE(golem.getCoords().first == 10);
            REQUIRE(golem.getCoords().second == 15);
            REQUIRE(golem.getMaxHp() == 10);
            REQUIRE(golem.getCurHp() == 10);
            REQUIRE(golem.getCeil() == Ceil::essence);
            REQUIRE(golem.getName() == "golem");
            REQUIRE(golem.getStatus() == Status::wandering);
            REQUIRE(golem.getFaction() == Faction::golem);
        }SECTION("Enemy")
        {
            Enemy enemy(Faction::golem, 10, {10, 15}, {10, 15}, "enemy", 100, 100, Status::wandering, 10);
            REQUIRE(enemy.getSpeed() == 10);
            REQUIRE(enemy.Damage().first == 10);
            REQUIRE(enemy.Damage().second == 15);
            REQUIRE(enemy.getCoords().first == 10);
            REQUIRE(enemy.getCoords().second == 15);
            REQUIRE(enemy.getMaxHp() == 100);
            REQUIRE(enemy.getCurHp() == 100);
            REQUIRE(enemy.getName() == "enemy");
            REQUIRE(enemy.getStatus() == Status::wandering);
            REQUIRE(enemy.getVision() == 10);
        }SECTION("LivingEnemy") {
            LivingEnemy livingEnemy(10, {10, 15}, {10, 15}, "livingEnemy", 100, 100);
            REQUIRE(livingEnemy.getSpeed() == 10);
            REQUIRE(livingEnemy.Damage().first == 10);
            REQUIRE(livingEnemy.Damage().second == 15);
            REQUIRE(livingEnemy.getCoords().first == 10);
            REQUIRE(livingEnemy.getCoords().second == 15);
            REQUIRE(livingEnemy.getMaxHp() == 100);
            REQUIRE(livingEnemy.getCurHp() == 100);
            REQUIRE(livingEnemy.getName() == "livingEnemy");
            REQUIRE(livingEnemy.getStatus() == Status::wandering);
            REQUIRE(livingEnemy.getFaction() == Faction::livingEnemy);
        } SECTION("Undead") {
            Undead undead(10, {10, 15}, {10, 15}, "undead", "living", 100, 100);
            REQUIRE(undead.getSpeed() == 10);
            REQUIRE(undead.Damage().first == 10);
            REQUIRE(undead.Damage().second == 15);
            REQUIRE(undead.getCoords().first == 10);
            REQUIRE(undead.getCoords().second == 15);
            REQUIRE(undead.getMaxHp() == 100);
            REQUIRE(undead.getCurHp() == 100);
            REQUIRE(undead.getName() == "undead");
            REQUIRE(undead.getStatus() == Status::wandering);
            REQUIRE(undead.getFaction() == Faction::undead);
        }
    }SECTION("getDamage") {
        Enemy enemy(Faction::golem, 10, {10, 15}, {10, 15}, "enemy", 100, 100, Status::wandering, 10);
        enemy.getDamage(10);
        REQUIRE(enemy.getCurHp() == 90);
    }SECTION("golemGetDamage") {
        Golem golem(10, {10, 15}, {10, 15}, 10, 100, Ceil::essence);
        golem.getDamage(100);
        REQUIRE(golem.getCurHp() == 10);
        golem.setHitPercentage(0);
        golem.getDamage(1);
        REQUIRE(golem.getCurHp() == 9);
    }SECTION("die") {
        Enemy enemy(Faction::golem, 10, {10, 15}, {10, 15}, "enemy", 100, 100, Status::wandering, 10);
        enemy.die();
        REQUIRE(enemy.getStatus() == Status::dead);
    }SECTION("attack") {
        Enemy enemy1(Faction::golem, 10, {10, 15}, {10, 15}, "enemy", 100, 100, Status::wandering, 10);
        Enemy enemy2(Faction::livingEnemy, 10, {10, 15}, {10, 15}, "enemy", 100, 100, Status::wandering, 10);
        enemy1.attack(enemy2);
        REQUIRE(enemy2.getCurHp() != 100);
        Enemy enemy3(Faction::golem, 10, {10, 15}, {10, 15}, "enemy", 1000, 1000, Status::wandering, 10);
        Enemy enemy4(Faction::golem, 10, {10, 15}, {10, 15}, "enemy", 1000, 1000, Status::wandering, 10);
        REQUIRE_THROWS(enemy3.attack(enemy4));
        enemy3.setFaction(Faction::livingEnemy);
        enemy3.setStatus(Status::dead);
        REQUIRE_THROWS(enemy3.attack(enemy2));
        enemy3.setStatus(Status::wandering);
        enemy1.setCoords({0, 0});
        REQUIRE_THROWS(enemy1.attack(enemy2));
        enemy3.setCoords({5, 5});
        enemy4.setCoords({5, 6});
        REQUIRE_NOTHROW(enemy3.attack(enemy4));
        enemy3.setCoords({5, 5});
        enemy4.setCoords({6, 6});
        REQUIRE_NOTHROW(enemy3.attack(enemy4));
        enemy3.setCoords({5, 5});
        enemy4.setCoords({5, 7});
        REQUIRE_THROWS(enemy3.attack(enemy4));

    }SECTION("doSomething") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[1][1]});
        Enemy enemy1(Faction::golem, 10, {10, 15}, {5, 5}, "enemy", 100, 100, Status::wandering, 10);
        Enemy enemy2(Faction::livingEnemy, 10, {10, 15}, {7, 7}, "enemy", 100, 100, Status::wandering, 10);
        LivingEnemy knight(10, {10, 20}, {4, 4}, "knigh", 100, 100);
        LivingEnemy knight2(10, {10, 20}, {5, 5}, "knigh2", 100, 100);
        Undead undead(10, {10, 20}, {20, 20}, "undead", "livingUndead", 100, 100);
        dungeon += {&enemy1, &dungeon.getMapLevel()[enemy1.getCoords().first][enemy1.getCoords().second]};
        dungeon += {&enemy2, &dungeon.getMapLevel()[enemy2.getCoords().first][enemy2.getCoords().second]};
        dungeon += {&knight, &dungeon.getMapLevel()[knight.getCoords().first][knight.getCoords().second]};
        dungeon += {&knight2, &dungeon.getMapLevel()[knight2.getCoords().first][knight2.getCoords().second]};
        Golem golem(10, {10, 15}, {2, 2}, 10, 100, Ceil::essence);
        dungeon += {&golem, &dungeon.getMapLevel()[golem.getCoords().first][golem.getCoords().second]};
        dungeon += {&undead, &dungeon.getMapLevel()[undead.getCoords().first][undead.getCoords().second]};
        SECTION("MOVE") {
            REQUIRE_NOTHROW(enemy1.move(matrix, {6, 6}, dungeon.getListEnemies()));
            enemy1.move(matrix, {6, 6}, dungeon.getListEnemies());
            REQUIRE(enemy1.getCoords().first == 5);
            REQUIRE(enemy1.getCoords().second == 6);
            REQUIRE_THROWS(enemy1.move(matrix, {1000, 1000}, dungeon.getListEnemies()));
            REQUIRE_THROWS(enemy1.move(matrix, {-1000, -1000}, dungeon.getListEnemies()));
            enemy1.move(matrix, {6, 6}, dungeon.getListEnemies());
            REQUIRE(enemy1.getCoords().first == 5);
            REQUIRE(enemy1.getCoords().second == 6);
            REQUIRE_THROWS(enemy1.move(matrix, {5, 6}, dungeon.getListEnemies()));

            Enemy enemy3(Faction::golem, 10, {10, 15}, {5, 5}, "enemy", 100, 100, Status::wandering, 10);
            REQUIRE_NOTHROW(enemy3.move(matrix, {5, 7}, dungeon.getListEnemies()));
            REQUIRE(enemy3.getCoords().first == 6);
            REQUIRE(enemy3.getCoords().second == 5);

        }SECTION("afterDie") {
            int x = golem.getCoords().second;
            int y = golem.getCoords().first;
            golem.die();
            REQUIRE(dungeon.getMapLevel()[y][x] == Ceil::floor);
            int size = dungeon.getListEnemies().size();
            golem.methodAfterDie(dungeon);
            REQUIRE(dungeon.getMapLevel()[y][x] == Ceil::essence);
            REQUIRE(dungeon.getListEnemies().size() == (size - 1));
            REQUIRE_THROWS(enemy1.methodAfterDie(dungeon));
            knight.die();
            knight.methodAfterDie(dungeon);
            REQUIRE(dungeon.getListEnemies().size() == (size - 1));
            undead.die();
            undead.methodAfterDie(dungeon);
            REQUIRE(dungeon.getListEnemies().size() == (size - 2));
            for (auto &item: dungeon.getListEnemies()) {
                REQUIRE_FALSE(item.first == &undead);
            }
            for (auto &item: dungeon.getListEnemies()) {
                REQUIRE_FALSE(item.first == &golem);
            }
            bool flag = false;
            for (auto &item: dungeon.getListEnemies()) {
                if (item.first == &knight) flag = true;
            }
            REQUIRE(flag);
        } SECTION("Become undead") {
            int size = dungeon.getListEnemies().size();
            LivingEnemy knight3(10, {10, 20}, {5, 5}, 100, 100);
            dungeon += {&knight3, &dungeon.getMapLevel()[knight3.getCoords().first][knight3.getCoords().second]};
            knight3.die();
            REQUIRE_NOTHROW(knight3.becomeUndead(dungeon));
            bool flag = false;
            for (auto &item: dungeon.getListEnemies()) {
                if (item.first->isHeap()) flag = true;
            }
            REQUIRE(flag);
        }

    }
}

TEST_CASE("Character") {
    SECTION("Constructor") {
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        REQUIRE(character.getSpeed() == 10);
        REQUIRE(character.Damage().first == 10);
        REQUIRE(character.Damage().second == 15);
        REQUIRE(character.getCoords().first == 2);
        REQUIRE(character.getCoords().second == 2);
        REQUIRE(character.getFaction() == Faction::character);
        REQUIRE(character.getLvl() == 1);
        REQUIRE(character.getCharacteristics().getMaxHp() == 100);
        REQUIRE(character.getCharacteristics().getCurHp() == 100);
        REQUIRE(character.getCharacteristics().getCurMana() == 100);
        REQUIRE(character.getCharacteristics().getMaxMana() == 100);
        REQUIRE(character.getExp() == 0);
        REQUIRE(character.getCountEssence() == 0);
        REQUIRE(character.getSideLooking() == Move::right);
    }SECTION("Action with skill table and upLVL") {
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        character.upLVL();
        REQUIRE(character.getLvl() == 2);
        REQUIRE(character.getLvlPoint() == 1);
        REQUIRE(character.getExp() == 0);
        REQUIRE(character.getCharacteristics().getMaxMana() == 150);
        REQUIRE(character.getCharacteristics().getMaxHp() == 150);
        REQUIRE(character.Damage().first == 15);
        REQUIRE(character.Damage().second == 20);
        Curse curse(10);
        Desiccation desiccation;
        Necromancy necromancy(10);
        Morphism morphism(10);
        REQUIRE_NOTHROW(character.getTableSkills().addSkill(&curse, "Curse"));
        REQUIRE_NOTHROW(character.getTableSkills().addSkill(&desiccation, "desiccation"));
        REQUIRE_NOTHROW(character.getTableSkills().addSkill(&necromancy, "Necromancy"));
        REQUIRE_NOTHROW(character.getTableSkills().addSkill(&morphism, "Morphism"));
        REQUIRE_NOTHROW(character.getTableSkills().upgradeSkill("desiccation"));
        REQUIRE_NOTHROW(character.getTableSkills().upgradeSkill("Curse"));
        REQUIRE_NOTHROW(character.getTableSkills().upgradeSkill("Necromancy"));
        REQUIRE_NOTHROW(character.getTableSkills().upgradeSkill("Morphism"));
        REQUIRE(character.getTableSkills().getSkill("Curse")->getSkillLvl() == 1);
        REQUIRE(character.getTableSkills().getSkill("desiccation")->getSkillLvl() == 1);
        REQUIRE(character.getTableSkills().getSkill("Necromancy")->getSkillLvl() == 1);
        REQUIRE(character.getTableSkills().getSkill("Morphism")->getSkillLvl() == 1);
        REQUIRE(character.getTableSkills().countSkills() == 4);
        REQUIRE_NOTHROW(character.upgradeSkill("Curse"));
        REQUIRE(character.getTableSkills().getSkill("Curse")->getSkillLvl() == 2);
        REQUIRE(character.upgradeSkill("Curse") == -1);
    } SECTION("Take dame and attack someone") {
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        character.getDamage(10);
        REQUIRE(character.getCharacteristics().getCurHp() == 90);
        character.getDamage(1000);
        REQUIRE(character.getCharacteristics().getCurHp() == 0);
        character.getCharacteristics().setCurHp(100);
        Enemy enemy1(Faction::golem, 10, {10, 15}, {6, 6}, "enemy", 100, 100, Status::wandering, 10);
        REQUIRE_THROWS(character.attack(enemy1));
        enemy1.setCoords({3, 3});
        REQUIRE_NOTHROW(character.attack(enemy1));
        REQUIRE(character.getExp() == 0);
        REQUIRE(enemy1.getCurHp() < 100);
        enemy1.die();
        REQUIRE_THROWS(character.attack(enemy1));
        enemy1.setStatus(Status::wandering);
        enemy1.setCurHp(1);
        TableSkills tableSkills2;
        Character character2(10, {10, 15}, {2, 2}, &tableSkills2);
        REQUIRE_NOTHROW(character2.attack(enemy1));
        REQUIRE(enemy1.getStatus() == Status::dead);
        REQUIRE(character2.getExp() != 0);
    } SECTION("Open and close door") {
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills2;
        Character character2(10, {10, 15}, {2, 2}, &tableSkills2);
        matrix[3][3] = Ceil::closeDoor;
        REQUIRE_NOTHROW(character2.open(matrix));
        REQUIRE(matrix[3][3] == Ceil::openDoor);
        matrix[3][3] = Ceil::closeDoor;
        REQUIRE_THROWS(character2.close(matrix));
        matrix[3][3] = Ceil::floor;
        matrix[5][5] = Ceil::closeDoor;
        REQUIRE_THROWS(character2.open(matrix));
        matrix[3][3] = Ceil::openDoor;
        REQUIRE_NOTHROW(character2.close(matrix));
        REQUIRE(matrix[3][3] == Ceil::closeDoor);
        matrix[3][3] = Ceil::openDoor;
        REQUIRE_THROWS(character2.open(matrix));
        matrix[3][3] = Ceil::floor;
        matrix[5][5] = Ceil::openDoor;
        REQUIRE_THROWS(character2.close(matrix));
    }SECTION("Move") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[2][2]});
        character.move(Move::right, dungeon);
        REQUIRE(character.getCoords().first == 2);
        REQUIRE(character.getCoords().second == 3);
        character.move(Move::left, dungeon);
        REQUIRE(character.getCoords().first == 2);
        REQUIRE(character.getCoords().second == 2);
        character.move(Move::down, dungeon);
        REQUIRE(character.getCoords().first == 1);
        REQUIRE(character.getCoords().second == 2);
        character.move(Move::up, dungeon);
        REQUIRE(character.getCoords().first == 2);
        REQUIRE(character.getCoords().second == 2);
        dungeon.getMapLevel()[3][2] = Ceil::wall;
        REQUIRE(character.move(Move::up, dungeon) == -1);
        dungeon.getMapLevel()[3][2] = Ceil::closeDoor;
        REQUIRE(character.move(Move::up, dungeon) == -1);
        character.open(dungeon.getMapLevel());
        REQUIRE(character.move(Move::up, dungeon) == 0);
        REQUIRE(character.getCoords().first == 3);
        REQUIRE(character.getCoords().second == 2);
    } SECTION("take Essence") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[1][1]});
        dungeon.getMapLevel()[2][2] = Ceil::essence;
        REQUIRE_NOTHROW(character.takeEssense(dungeon));
        REQUIRE(character.getCountEssence() == 50);
        REQUIRE(dungeon.getMapLevel()[2][2] == Ceil::floor);
        REQUIRE(character.takeEssense(dungeon) == -1);
        REQUIRE(character.getCountEssence() == 50);
    }SECTION ("Open units") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[2][2]});
        REQUIRE_NOTHROW(character.setCountEssence(1));
        REQUIRE(character.openEnemy(dungeon) == -1);
        LivingEnemy knight(10, {10, 20}, {3, 3}, 100, 100);
        dungeon += {&knight, &dungeon.getMapLevel()[knight.getCoords().first][knight.getCoords().second]};
        REQUIRE_NOTHROW(character.setCountEssence(0));
        REQUIRE(character.openEnemy(dungeon) == -3);
        REQUIRE_NOTHROW(character.setCountEssence(1));
        knight.die();
        REQUIRE(character.openEnemy(dungeon) == -2);
        REQUIRE_NOTHROW(character.setCountEssence(1000));
        REQUIRE_NOTHROW(character.openEnemy(dungeon));
        REQUIRE(character.getOpenEnemies()[0] == "livingEnemy");
        int size = character.getOpenEnemies().size();
        REQUIRE_NOTHROW(character.openEnemy(dungeon));
        REQUIRE(size == character.getOpenEnemies().size());
        LivingSummoner summoner(10, {10, 10}, {1, 1}, 100);
        dungeon += {&summoner, &dungeon.getMapLevel()[summoner.getCoords().second][summoner.getCoords().first]};

        REQUIRE_NOTHROW(character.openEnemy(dungeon));
        REQUIRE(size == character.getOpenEnemies().size());
        summoner.die();
        REQUIRE_NOTHROW(character.openEnemy(dungeon));
        REQUIRE(size + 1 == character.getOpenEnemies().size());
        REQUIRE(character.getOpenEnemies()[1] == "livingSummoner");
        REQUIRE_NOTHROW(character.openEnemy(dungeon));
        REQUIRE(size + 1 == character.getOpenEnemies().size());
    }SECTION("attackSomeone") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[2][2]});
        LivingEnemy knight(10, {10, 20}, {3, 3}, 30, 30);
        dungeon += {&knight, &dungeon.getMapLevel()[knight.getCoords().first][knight.getCoords().second]};
        REQUIRE_NOTHROW(character.attackSomeone(dungeon));
        REQUIRE(knight.getCurHp() != knight.getMaxHp());
        REQUIRE_NOTHROW(character.attackSomeone(dungeon));
        REQUIRE_NOTHROW(character.attackSomeone(dungeon));
        REQUIRE_NOTHROW(character.attackSomeone(dungeon));
        REQUIRE(knight.getStatus() == Status::dead);
        REQUIRE(character.attackSomeone(dungeon) == -1);
        LivingEnemy knight2(10, {10, 20}, {5, 3}, 30, 30);
        dungeon += {&knight2, &dungeon.getMapLevel()[knight.getCoords().first][knight.getCoords().second]};
        REQUIRE(character.attackSomeone(dungeon) == -1);
    }
}

TEST_CASE("Test character`s skills") {
    SECTION("Curse") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[2][2]});
        LivingEnemy knight(10, {10, 20}, {4, 4}, 100, 100);
        LivingEnemy knight2(10, {10, 20}, {5, 5}, 100, 100);
        Undead undead(10, {10, 20}, {20, 20}, 100, 100);
        Golem golem(10, {10, 15}, {3, 3}, 100, 0, Ceil::essence);
        dungeon += {&knight, &dungeon.getMapLevel()[knight.getCoords().first][knight.getCoords().second]};
        dungeon += {&knight2, &dungeon.getMapLevel()[knight2.getCoords().first][knight2.getCoords().second]};
        dungeon += {&golem, &dungeon.getMapLevel()[golem.getCoords().first][golem.getCoords().second]};
        dungeon += {&undead, &dungeon.getMapLevel()[undead.getCoords().first][undead.getCoords().second]};
        Curse curse(10);
        REQUIRE_NOTHROW(character.getTableSkills().addSkill(&curse, "Curse"));
        REQUIRE_NOTHROW(character.getTableSkills().upgradeSkill("Curse"));
        REQUIRE_NOTHROW(character.useSkill("Curse", dungeon));
        REQUIRE(golem.getCurHp() != golem.getMaxHp());
        golem.setCurHp(golem.getMaxHp());
        character.setSideLooking(Move::up);
        REQUIRE_NOTHROW(character.useSkill("Curse", dungeon));
        bool flag = true;
        for (auto &item: dungeon.getListEnemies()) {
            if (item.first->getCurHp() != item.first->getMaxHp()) flag = false;
        }
        REQUIRE(flag);
    } SECTION("Desiccation") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[2][2]});
        LivingEnemy knight(10, {10, 20}, {2, 2}, 100, 100);
        LivingEnemy knight2(10, {10, 20}, {2, 2}, 100, 100);
        Undead undead(10, {10, 20}, {20, 20}, 100, 100);
        Golem golem(10, {10, 15}, {3, 3}, 100, 0, Ceil::essence);
        dungeon += {&knight, &dungeon.getMapLevel()[knight.getCoords().first][knight.getCoords().second]};
        dungeon += {&knight2, &dungeon.getMapLevel()[knight2.getCoords().first][knight2.getCoords().second]};
        dungeon += {&golem, &dungeon.getMapLevel()[golem.getCoords().first][golem.getCoords().second]};
        dungeon += {&undead, &dungeon.getMapLevel()[undead.getCoords().first][undead.getCoords().second]};
        Desiccation desiccation;
        REQUIRE_NOTHROW(character.getCharacteristics().setCurHp(50));
        REQUIRE_NOTHROW(character.getTableSkills().addSkill(&desiccation, "desiccation"));
        REQUIRE_NOTHROW(character.useSkill("desiccation", dungeon));
        REQUIRE(character.getCharacteristics().getCurHp() == 50);
        REQUIRE_NOTHROW(character.getTableSkills().upgradeSkill("desiccation"));
        REQUIRE_NOTHROW(character.useSkill("desiccation", dungeon));
        REQUIRE(character.getCharacteristics().getCurHp() == 50);
        knight.die();
        int size = dungeon.getListEnemies().size();
        REQUIRE_NOTHROW(character.useSkill("desiccation", dungeon));
        REQUIRE(character.getCharacteristics().getCurHp() == 100);
        REQUIRE(size - 1 == dungeon.getListEnemies().size());
        knight2.die();
        size = dungeon.getListEnemies().size();
        REQUIRE_NOTHROW(character.getCharacteristics().setCurMana(50));
        REQUIRE_NOTHROW(character.useSkill("desiccation", dungeon));
        REQUIRE(character.getCharacteristics().getCurMana() == 100);
        REQUIRE(size - 1 == dungeon.getListEnemies().size());

        REQUIRE_NOTHROW(character.getCharacteristics().setCurHp(50));
        REQUIRE_NOTHROW(character.useSkill("desiccation", dungeon));
        REQUIRE(character.getCharacteristics().getCurHp() == 50);
    } SECTION("Necromancy") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[2][2]});
        LivingEnemy knight(10, {10, 20}, {3, 2}, 100, 100);
        LivingSummoner summoner(10, {10, 10}, {1, 1}, 100);
        Undead undead(10, {10, 20}, {20, 20}, 100, 100);
        Golem golem(10, {10, 15}, {3, 3}, 100, 0, Ceil::essence);
        dungeon += {&knight, &dungeon.getMapLevel()[knight.getCoords().second][knight.getCoords().first]};
        dungeon += {&summoner, &dungeon.getMapLevel()[summoner.getCoords().second][summoner.getCoords().first]};
        dungeon += {&golem, &dungeon.getMapLevel()[golem.getCoords().second][golem.getCoords().first]};
        dungeon += {&undead, &dungeon.getMapLevel()[undead.getCoords().second][undead.getCoords().first]};

        Necromancy necromancy(10);
        REQUIRE_NOTHROW(character.getTableSkills().addSkill(&necromancy, "necromancy"));
        REQUIRE_NOTHROW(character.useSkill("necromancy", dungeon));
        REQUIRE_NOTHROW(character.getTableSkills().upgradeSkill("necromancy"));
        REQUIRE_NOTHROW(character.useSkill("necromancy", dungeon));
        bool flag = true;
        for (auto &item: dungeon.getListEnemies()) {
            if (item.first->getFaction() == Faction::character) flag = false;
        }
        character.getOpenEnemies().emplace_back("livingSummoner");
        character.getOpenEnemies().emplace_back("livingEnemy");
        REQUIRE_NOTHROW(character.useSkill("necromancy", dungeon));
        flag = true;
        for (auto &item: dungeon.getListEnemies()) {
            if (item.first->getFaction() == Faction::character) flag = false;
        }
        REQUIRE(flag);
        summoner.die();
        REQUIRE_NOTHROW(character.useSkill("necromancy", dungeon));
        flag = false;
        for (auto &item: dungeon.getListEnemies()) {
            if (item.first->getFaction() == Faction::character && item.first->getName() == "undeadSummoner")
                flag = true;
        }
        REQUIRE(flag);
        character.setCoords({50, 50});
        REQUIRE_NOTHROW(character.useSkill("necromancy", dungeon));
        flag = true;
        for (auto &item: dungeon.getListEnemies()) {
            if (item.first->getFaction() == Faction::character) flag = false;
        }


    }SECTION("Morphism") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[2][2]});
        LivingEnemy knight(10, {10, 20}, {3, 2}, 100, 100);
        UndeadSummoner undeadSummoner(10, {10, 10}, {3, 3}, 100, 100);
        Undead undead(10, {10, 20}, {4, 4}, 100, 100);
        Golem golem(10, {10, 15}, {3, 3}, 100, 0, Ceil::essence);
        dungeon += {&knight, &dungeon.getMapLevel()[knight.getCoords().second][knight.getCoords().first]};
        dungeon += {&undeadSummoner,
                    &dungeon.getMapLevel()[undeadSummoner.getCoords().second][undeadSummoner.getCoords().first]};
        dungeon += {&golem, &dungeon.getMapLevel()[golem.getCoords().second][golem.getCoords().first]};
        dungeon += {&undead, &dungeon.getMapLevel()[undead.getCoords().second][undead.getCoords().first]};

        Morphism morphism(10);
        int mas[1] = {3};
        REQUIRE_NOTHROW(character.getTableSkills().addSkill(&morphism, "morphism"));
        REQUIRE_NOTHROW(character.useSkill("morphism", dungeon, mas));
        REQUIRE_NOTHROW(character.getTableSkills().upgradeSkill("morphism"));
        REQUIRE_NOTHROW(character.useSkill("morphism", dungeon, mas));


        character.getOpenEnemies().emplace_back("livingSummoner");
        character.getOpenEnemies().emplace_back("livingEnemy");
        REQUIRE_NOTHROW(character.useSkill("morphism", dungeon, mas));
        bool flag = true;
        for (auto &item: dungeon.getListEnemies()) {
            if (item.first->getName() == "undead") flag = false;
        }
        REQUIRE(flag);
        character.getOpenEnemies().emplace_back("livingEnemy");
        int mas2[1] = {2};
        REQUIRE_NOTHROW(character.useSkill("morphism", dungeon, mas2));
        REQUIRE_NOTHROW(character.useSkill("morphism", dungeon, mas2));
        flag = true;
        for (auto &item: dungeon.getListEnemies()) {
            if (item.first->getName() == "undeadSummoner") flag = false;
        }
        REQUIRE(flag);
        REQUIRE_NOTHROW(character.useSkill("morphism", dungeon, mas2));
    }
}


TEST_CASE("Summoner") {
    SECTION("livingSummoner") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[2][2]});
        LivingSummoner livingSummoner(10, {10, 15}, {10, 10}, 100);
        dungeon += {&livingSummoner,
                    &dungeon.getMapLevel()[livingSummoner.getCoords().second][livingSummoner.getCoords().first]};
        int size = dungeon.getListEnemies().size();
        livingSummoner.getDamage(10);
        REQUIRE_NOTHROW(livingSummoner.summon(dungeon, livingSummoner.getCoords(), 2,
                                              livingSummoner.getCurHp()));
        REQUIRE(size + 4 == dungeon.getListEnemies().size());
        REQUIRE_THROWS(livingSummoner.summon(dungeon, livingSummoner.getCoords(), 2,
                                             livingSummoner.getCurHp()));
        for (auto &item: dungeon.getListEnemies()) {
            if (item.first->getName() != "livingSummoner" || item.first->getName() != "undeadSummoner") {
                item.first->die();
            }
        }
        REQUIRE_NOTHROW(dungeon.allDoSomething());
        size = dungeon.getListEnemies().size();
        livingSummoner.getDamage(10);
        REQUIRE_NOTHROW(livingSummoner.summon(dungeon, livingSummoner.getCoords(), 2,
                                              livingSummoner.getCurHp()));
        REQUIRE(size + 4 == dungeon.getListEnemies().size());
        REQUIRE_THROWS(livingSummoner.summon(dungeon, livingSummoner.getCoords(), 2,
                                             livingSummoner.getCurHp()));
        for (auto &item: dungeon.getListEnemies()) {
            if (item.first->getName() != "livingSummoner" || item.first->getName() != "undeadSummoner") {
                item.first->die();
            }
        }
        REQUIRE_NOTHROW(dungeon.allDoSomething());
        size = dungeon.getListEnemies().size();
        livingSummoner.getDamage(10);
        dungeon.getMapLevel()[livingSummoner.getCoords().second][livingSummoner.getCoords().first] = Ceil::wall;
        REQUIRE_THROWS(livingSummoner.summon(dungeon, livingSummoner.getCoords(), 2,
                                             livingSummoner.getCurHp()));
        REQUIRE(size == dungeon.getListEnemies().size());


    }SECTION("undeadSummoner") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[2][2]});
        UndeadSummoner undeadSummoner(10, {10, 15}, {10, 10}, 100, 100);
        dungeon += {&undeadSummoner,
                    &dungeon.getMapLevel()[undeadSummoner.getCoords().second][undeadSummoner.getCoords().first]};
        int size = dungeon.getListEnemies().size();
        undeadSummoner.getDamage(10);
        REQUIRE_NOTHROW(undeadSummoner.summon(dungeon, undeadSummoner.getCoords(), 2,
                                              undeadSummoner.getCurHp()));
        REQUIRE(size + 4 == dungeon.getListEnemies().size());
        REQUIRE_THROWS(undeadSummoner.summon(dungeon, undeadSummoner.getCoords(), 2,
                                             undeadSummoner.getCurHp()));
        for (auto &item: dungeon.getListEnemies()) {
            if (item.first->getName() != "livingSummoner" || item.first->getName() != "undeadSummoner") {
                item.first->die();
            }
        }
        REQUIRE_NOTHROW(dungeon.allDoSomething());
        size = dungeon.getListEnemies().size();
        undeadSummoner.getDamage(10);
        REQUIRE_NOTHROW(undeadSummoner.summon(dungeon, undeadSummoner.getCoords(), 2,
                                              undeadSummoner.getCurHp()));
        REQUIRE(size + 4 == dungeon.getListEnemies().size());

        REQUIRE_THROWS(undeadSummoner.summon(dungeon, undeadSummoner.getCoords(), 2,
                                             undeadSummoner.getCurHp()));
        for (auto &item: dungeon.getListEnemies()) {
            if (item.first->getName() != "livingSummoner" || item.first->getName() != "undeadSummoner") {
                item.first->die();
            }
        }
        REQUIRE_NOTHROW(dungeon.allDoSomething());
        size = dungeon.getListEnemies().size();
        undeadSummoner.getDamage(10);
        dungeon.getMapLevel()[undeadSummoner.getCoords().second][undeadSummoner.getCoords().first] = Ceil::wall;
        REQUIRE_THROWS(undeadSummoner.summon(dungeon, undeadSummoner.getCoords(), 2,
                                             undeadSummoner.getCurHp()));
        REQUIRE(size == dungeon.getListEnemies().size());
    }
}

TEST_CASE("Funcion dosomething") {
    SECTION("Enemies") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[2][2]});
        LivingEnemy knight(10, {10, 20}, {50, 50}, 100, 100);
        dungeon += {&knight, &dungeon.getMapLevel()[knight.getCoords().second][knight.getCoords().first]};
        REQUIRE_NOTHROW(knight.doSomething(dungeon));
        Undead undead(10, {10, 20}, {51, 51}, 100, 100);
        dungeon += {&undead, &dungeon.getMapLevel()[undead.getCoords().second][undead.getCoords().first]};
        REQUIRE_NOTHROW(knight.doSomething(dungeon));
        REQUIRE_NOTHROW(knight.doSomething(dungeon));
        REQUIRE(undead.getCurHp() != undead.getMaxHp());
    } SECTION("undeadSummoner") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[2][2]});
        LivingSummoner livingSummoner(10, {10, 20}, {50, 50}, 100);
        dungeon += {&livingSummoner,
                    &dungeon.getMapLevel()[livingSummoner.getCoords().second][livingSummoner.getCoords().first]};
        livingSummoner.getDamage(10);
        REQUIRE_NOTHROW(livingSummoner.doSomething(dungeon));
        Undead undead(10, {10, 20}, {51, 51}, 100, 100);
        dungeon += {&undead, &dungeon.getMapLevel()[undead.getCoords().second][undead.getCoords().first]};
        REQUIRE_NOTHROW(livingSummoner.doSomething(dungeon));
        REQUIRE(dungeon.getListEnemies().size() == 6);
        REQUIRE_NOTHROW(livingSummoner.doSomething(dungeon));
        REQUIRE(dungeon.getListEnemies().size() == 6);
        REQUIRE(undead.getCurHp() != undead.getMaxHp());
    }SECTION("livingSummoner") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[2][2]});
        UndeadSummoner livingSummoner(10, {10, 20}, {50, 50}, 100, 100);
        dungeon += {&livingSummoner,
                    &dungeon.getMapLevel()[livingSummoner.getCoords().second][livingSummoner.getCoords().first]};
        livingSummoner.getDamage(10);
        REQUIRE_NOTHROW(livingSummoner.doSomething(dungeon));
        LivingEnemy undead(10, {10, 20}, {51, 51}, 100, 100);
        dungeon += {&undead, &dungeon.getMapLevel()[undead.getCoords().second][undead.getCoords().first]};
        REQUIRE_NOTHROW(livingSummoner.doSomething(dungeon));
        REQUIRE(dungeon.getListEnemies().size() == 6);
        REQUIRE_NOTHROW(livingSummoner.doSomething(dungeon));
        REQUIRE(dungeon.getListEnemies().size() == 6);
        REQUIRE(undead.getCurHp() != undead.getMaxHp());
    }
}


TEST_CASE("Dungeom") {
    SECTION("allDoSomething") {
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(100, 100);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        TableSkills tableSkills;
        Character character(10, {10, 15}, {2, 2}, &tableSkills);
        Dungeon dungeon(listEnemies, matrix, matrix.cols(), matrix.rows(), {&character, &matrix[2][2]});
        LivingEnemy knight(10, {10, 20}, {3, 2}, 100, 100);
        UndeadSummoner undeadSummoner(10, {10, 10}, {3, 3}, 100, 100);
        Undead undead(10, {10, 20}, {4, 4}, 100, 100);
        Golem golem(10, {10, 15}, {3, 3}, 100, 0, Ceil::essence);
        dungeon += {&knight, &dungeon.getMapLevel()[knight.getCoords().second][knight.getCoords().first]};
        dungeon += {&undeadSummoner,
                    &dungeon.getMapLevel()[undeadSummoner.getCoords().second][undeadSummoner.getCoords().first]};
        dungeon += {&golem, &dungeon.getMapLevel()[golem.getCoords().second][golem.getCoords().first]};
        dungeon += {&undead, &dungeon.getMapLevel()[undead.getCoords().second][undead.getCoords().first]};

        golem.die();
        REQUIRE_NOTHROW(dungeon.allDoSomething());
    }
}

TEST_CASE("Game") {
    SECTION("game") {
        Game game;
        std::list<std::pair<Enemy *, Ceil *>> listEnemies;
        Matrix<Ceil> matrix(10, 10);
        for (auto &item: matrix) {
            item = Ceil::floor;
        }
        Dungeon dungeon1(listEnemies, matrix, matrix.cols(), matrix.rows(),
                         {&game.getHero(),
                          &matrix[game.getHero().getCoords().second][game.getHero().getCoords().first]});
        Matrix<Ceil> matrix2(10, 10);
        for (auto &item: matrix2) {
            item = Ceil::lava;
        }

        Dungeon dungeon2(listEnemies, matrix2, matrix2.cols(), matrix2.rows(),
                         {&game.getHero(),
                          &matrix[game.getHero().getCoords().second][game.getHero().getCoords().first]});

        std::vector<Dungeon> allmap;
        allmap.emplace_back(dungeon1);
        allmap.emplace_back(dungeon2);
        game.setAllMap(allmap);
        LivingEnemy knight(10, {10, 20}, {3, 2}, 100, 100);
        UndeadSummoner undeadSummoner(10, {10, 10}, {3, 3}, 100, 100);
        Undead undead(10, {10, 20}, {4, 4}, 100, 100);
        Golem golem(10, {10, 15}, {3, 3}, 100, 0, Ceil::essence);
        game.getAllMap()[0] += {&knight,
                                &game.getAllMap()[0].getMapLevel()[knight.getCoords().second][knight.getCoords().first]};
        game.getAllMap()[0] += {&undeadSummoner,
                                &game.getAllMap()[0].getMapLevel()[undeadSummoner.getCoords().second][undeadSummoner.getCoords().first]};
        game.getAllMap()[0] += {&golem,
                                &game.getAllMap()[0].getMapLevel()[golem.getCoords().second][golem.getCoords().first]};
        game.getAllMap()[0] += {&undead,
                                &game.getAllMap()[0].getMapLevel()[undead.getCoords().second][undead.getCoords().first]};

        int options[] = {1};
        REQUIRE_NOTHROW(game.makeTick(options));
        while (game.getHero().getCharacteristics().getCurHp() != 0) {
            game.makeTick();
        }

        REQUIRE(true);
    }
}











