//
// Created by sakhd on 18.11.2023.
//

#ifndef GAMELAB3_CURSE_H
#define GAMELAB3_CURSE_H

#include "../Skills.h"
#include "../../../../Dungeon/Dungeon.h"

///Проклятие предназначено для нанесения дистанционного магического урона
///по врагам, размер которого зависит от изученности навыка.
class Curse : public Skill {
private:
    int skillRange = 10;///< Дальность скилла
    /// Метод который определяет - координаты подходят под условие куда смотрит герой или нет
    /// \param side - сторона куда смотрит персонаж
    /// \param ax - его x
    /// \param ay - его y
    /// \param bx - чужой x
    /// \param by - чужой y
    /// \return true - ok, false - not ok
    bool check(Move side, int ax, int ay, int bx, int by) {
        if (side == Move::right) {
            if (ax <= bx) return true;
        } else if (side == Move::left) {
            if (ax >= bx) return true;
        } else if (side == Move::up) {
            if (ay >= by) return true;
        } else if (side == Move::down) { if (ay <= by) return true; }
        return false;
    }

public:
    /// Конструктор
    /// \param manaCost
    explicit Curse(int manaCost) : Skill(manaCost) {};

    /// Использовать скилл
    /// \param dungeon - уровень
    /// \param mas - опции
    /// \return 0 успех
    int useSkill(Dungeon &dungeon, int mas[]) override {
        if (skillLvl == 0) return -1;
        if (dungeon.getHero().first->getCharacteristics().getCurMana() < manaCost * skillLvl) return -2;
        Move side = dungeon.getHero().first->getSideLooking();
        int y = dungeon.getHero().first->getCoords().first;
        int x = dungeon.getHero().first->getCoords().second;
        Enemy *enemy = nullptr;
        int h = 1000000000;
        auto item = dungeon.getListEnemies().begin();
        for (item = dungeon.getListEnemies().begin(); item != dungeon.getListEnemies().end(); ++item) {
            if (abs(item->first->getCoords().second - x) + abs(item->first->getCoords().first - y) < h &&
                check(side, x, y, item->first->getCoords().second, item->first->getCoords().first) &&
                item->first->getStatus() != Status::dead) {
                h = abs(item->first->getCoords().second - x) + abs(item->first->getCoords().first - y);
                enemy = item->first;
            }
        }
        if (h > skillRange) return -3;
        if (enemy == nullptr) return -4;
        dungeon.getHero().first->getCharacteristics().mana(-1 * manaCost * skillLvl / 2);
        enemy->getDamage(
                (rand() % (dungeon.getHero().first->Damage().second - dungeon.getHero().first->Damage().first + 1) +
                 dungeon.getHero().first->Damage().first) * skillLvl);
        return 0;
    }

};


#endif //GAMELAB3_CURSE_H
