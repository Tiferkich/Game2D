//
// Created by sakhd on 24.10.2023.
//
#include <iostream>
#include <utility>
#include <vector>

#ifndef GAMELAB3_ISUMMONER_H
#define GAMELAB3_ISUMMONER_H

#include "../Enemy.h"
#include "../Undead/Undead.h"
#include "../LivingEnemy/LivingEnemy.h"
#include "../../../Dungeon/Dungeon.h"

///Класс от которого наследуются саммонеры
class Isummoner {
private:
    int curHp;///< Его прошлое здоровье
    bool flag = false; ///< Если true, то может призвать
    /// Проверяет есть ли рядом стена или нет
    /// \param matrix - карта
    /// \param coords - координаты, где саммонер стоит
    /// \return true если есть стены или дверь
    bool checkNear(Matrix<Ceil> &matrix, std::pair<int, int> coords) {
        bool flag0 = false;
        int dx[6] = {1, 0, -1, 0, 1, 0};   // смещения, соответствующие соседям ячейки
        int dy[6] = {0, 1, 0, -1, 1, 0};
        int x, y;
        for (int i = 0; i < 6; i++) {
            if (flag0) { break; }
            x = coords.second + dx[i];
            y = coords.first + dy[i];
            if (matrix[y][x] == Ceil::closeDoor || matrix[y][x] == Ceil::wall) flag0 = true;
        }
        return flag0;
    }


public:
    /// Конструктор
    /// \param curHp сюда подается максимальное здоровье саммонера
    explicit Isummoner(int curHp) : curHp(curHp) {};

    /// Проверка на получение дамага
    /// \param newCurHp - если новое хп меньше старого, то он призывает
    bool checkFlag(int newCurHp) {
        if (curHp > newCurHp * 2) {
            curHp = newCurHp;
            return true;
        }
        return false;
    }

    ///  Метода, который добавляет врагов на карту
    /// \param dungeon - уровень
    /// \param coords - координаты
    /// \param ratio - коэф усиления юнитов
    virtual void generateSummons(Dungeon &dungeon, std::pair<int, int> coords, int ratio, Faction faction) {
        if (ratio < 1) {
            ratio = 1;
        }

        dungeon.getListEnemies().push_back(
                {new Undead(10, {3 * ratio, 5 * ratio}, {coords.second - 1, coords.first},
                            20 * ratio, 20 * ratio), &(dungeon.getMapLevel()[coords.first][coords.second])});
        (--dungeon.getListEnemies().end())->first->setHeap(true);
        (--dungeon.getListEnemies().end())->first->setFaction(faction);
        dungeon.getListEnemies().push_back(
                {new Undead(10, {3 * ratio, 5 * ratio}, {coords.first + 1, coords.second},
                            20 * ratio, 20 * ratio), &(dungeon.getMapLevel()[coords.first + 1][coords.second])});
        (--dungeon.getListEnemies().end())->first->setHeap(true);
        (--dungeon.getListEnemies().end())->first->setFaction(faction);

        dungeon.getListEnemies().push_back(
                {new Undead(10, {3 * ratio, 5 * ratio}, {coords.first, coords.second + 1},
                            20 * ratio, 20 * ratio), &(dungeon.getMapLevel()[coords.first][coords.second + 1])});
        (--dungeon.getListEnemies().end())->first->setHeap(true);
        (--dungeon.getListEnemies().end())->first->setFaction(faction);

        dungeon.getListEnemies().push_back(
                {new Undead(10, {3 * ratio, 5 * ratio}, {coords.first, coords.second - 1},
                            20 * ratio, 20 * ratio), &(dungeon.getMapLevel()[coords.first][coords.second - 1])});
        (--dungeon.getListEnemies().end())->first->setHeap(true);
        (--dungeon.getListEnemies().end())->first->setFaction(faction);
    };

    /// \param dungeon - Уровень
    /// \param coords - Координаты призывателя
    /// \param ratio - коэф усиления
    /// \param newCurHp - новое текущее хп
    virtual void summon(Dungeon &dungeon, std::pair<int, int> coords, int ratio, int newCurHp, Faction faction) {
        if (!checkFlag(newCurHp)) {
            throw std::invalid_argument("Cannot summon");
        }
        if ((coords.first + 1 > dungeon.getMapLevel().rows() || coords.second + 1 > dungeon.getMapLevel().cols() ||
             coords.second - 1 < 0 || coords.first - 1 < 0) && checkNear(dungeon.getMapLevel(), coords))
            throw std::invalid_argument("Bad coords");
        generateSummons(dungeon, coords, ratio, faction);

    }

    /// Setter
    /// \param flag0 Установить флаг, для призыва
    void setFlag(bool flag0) {
        flag = flag0;
        return;
    }

};


#endif //GAMELAB3_ISUMMONER_H
