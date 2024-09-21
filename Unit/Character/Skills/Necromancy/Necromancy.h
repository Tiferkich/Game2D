//
// Created by sakhd on 18.11.2023.
//

#ifndef GAMELAB3_NECROMANCY_H
#define GAMELAB3_NECROMANCY_H

#include "../Skills.h"
#include "../../../../Dungeon/Dungeon.h"
#include "../../../Enemy/LivingEnemy/LivingEnemy.h"
#include "../../../Enemy/Summoner/LivingSummoner.h"
#include <iostream>

///Некромантия - заклинание создающее известные некроманту виды нежити (зомби, гуль, упырь, скелет...) в качестве прислужников из
///поверженных живых врагов затрачивая ману, затраты которой зависят от изученности навыка.
class Necromancy : public Skill {
private:

    bool checkNear(std::pair<int, int> coords, std::pair<int, int> anotherCoords) {
        bool flag = false;
        int dx[9] = {1, 0, -1, 0, 1, 0, 1, -1, -1};   // смещения, соответствующие соседям ячейки
        int dy[9] = {0, 1, 0, -1, 1, 0, -1, -1, 1};
        for (int i = 0; i < 9; i++) {
            if (flag) { return true; }
            int x = coords.second + dx[i];
            int y = coords.first + dy[i];
            if (x == anotherCoords.second && y == anotherCoords.first) flag = true;
        }
        return false;
    }

public:
    /// Конструктор
    /// \param manaCost - мана кост
    Necromancy(int manaCost) : Skill(manaCost) {};


    /// Использование некромантии
    /// \param dungeon - уровень
    /// \param mas - опции, в данном случае их можно не подавать
    /// \return 0 успех
    int useSkill(Dungeon &dungeon, int mas[]) override {
        if (skillLvl == 0) return -3;
        if (dungeon.getHero().first->getCountSummons(dungeon) == dungeon.getHero().first->getLvl()) return -2;
        if (dungeon.getHero().first->getCharacteristics().getCurMana() < manaCost * skillLvl) return -2;
        auto item = dungeon.getListEnemies().begin();
        Enemy *enemy = nullptr;
        for (item = dungeon.getListEnemies().begin(); item != dungeon.getListEnemies().end(); item++) {
            if (item->first->getStatus() == Status::dead && item->first->getFaction() == Faction::livingEnemy &&
                checkNear({dungeon.getHero().first->getCoords().first, dungeon.getHero().first->getCoords().second},
                          {item->first->getCoords().first, item->first->getCoords().second}) &&
                dungeon.getHero().first->isOpenEnemy(item->first->getName())) {
                enemy = item->first;
            }
        }
        if (enemy == nullptr) return -1;
        (dynamic_cast<LivingEnemy *> (enemy))->becomeUndead(dungeon);
        dungeon.getHero().first->getCharacteristics().mana(-1 * manaCost * skillLvl / 2);
        return 0;
    }

};


#endif //GAMELAB3_NECROMANCY_H
