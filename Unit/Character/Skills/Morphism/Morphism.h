//
// Created by sakhd on 19.11.2023.
//

#ifndef GAMELAB3_MORPHISM_H
#define GAMELAB3_MORPHISM_H

#include "../../../../Game/Game.h"
#include "../Skills.h"
#include "../../../../Dungeon/Dungeon.h"



///С помощью морфизма некромант может превратить нежить одного вида в другую (например, гоблин-скелета в гоблин-
///туля), если ему известно и вид нежити который превращает(скелет), и в который превращает(гуль), при
///этом затратив на это некоторое количество маны
class Morphism : public Skill {
private:
    int skillRange = 10; ///< Дальность использования скилла
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
            if (ay <= by) return true;
        } else if (side == Move::down) { if (ay >= by) return true; }
        return false;
    }


public:
    /// Конструктор
    /// \param manaCost - мана кост
    explicit Morphism(int manaCost) : Skill(manaCost) {};

    ///  Использование скилла
    /// \param dungeon - уровень
    /// \param mas - опции
    /// \return 0 успех
    int useSkill(Dungeon &dungeon, int mas[]) override {
        if (skillLvl == 0) return -1;
        std::string nameMorph = Game::allTypesEnemies[mas[0]];
        //if (!dungeon.getHero().first->isOpenEnemy(nameMorph)) return -2;
        if (dungeon.getHero().first->getCharacteristics().getCurMana() < manaCost * skillLvl) return -3;
        Move side = dungeon.getHero().first->getSideLooking();
        int y = dungeon.getHero().first->getCoords().first;
        int x = dungeon.getHero().first->getCoords().second;
        Enemy *enemy = nullptr;
        int h = 10000000;
        auto item = dungeon.getListEnemies().begin();
        for (item = dungeon.getListEnemies().begin(); item != dungeon.getListEnemies().end(); ++item) {
            if (check(side, x, y, item->first->getCoords().second, item->first->getCoords().first) &&
                abs(item->first->getCoords().second - x) + abs(item->first->getCoords().first - y) < h &&
                (item->first->getFaction() == Faction::character || item->first->getFaction() == Faction::undead)) {
                try {
                    if (dungeon.getHero().first->isOpenEnemy(dynamic_cast<Undead *>(item->first)->getNameLiving()) &&
                        item->first->getName() != nameMorph) {
                        h = abs(item->first->getCoords().second - x) + abs(item->first->getCoords().first - y);
                        enemy = item->first;
                    }
                } catch (...) {
                    continue;
                }
            }
        }
        if (enemy == nullptr) return -4;
        if (h > skillRange) return -5;

        if (nameMorph == "undead" && dungeon.getHero().first->isOpenEnemy("livingEnemy")) {
            dungeon.getListEnemies().push_back(
                    {new Undead(10, enemy->Damage(), enemy->getCoords(), "undead",
                                "livingEnemy",
                                enemy->getMaxHp(), enemy->getCurHp()),
                     &(dungeon.getMapLevel()[enemy->getCoords().second][enemy->getCoords().first])});
            (--dungeon.getListEnemies().end())->first->setHeap(true);
            (--dungeon.getListEnemies().end())->first->setFaction(enemy->getFaction());
            enemy->die();
            enemy->methodAfterDie(dungeon);
            dungeon.getHero().first->getCharacteristics().mana(manaCost * skillLvl / 2);
        } else if (nameMorph == "undeadSummoner" && dungeon.getHero().first->isOpenEnemy("livingSummoner")) {
            dungeon.getListEnemies().push_back(
                    {new UndeadSummoner(10, enemy->Damage(), enemy->getCoords(), enemy->getMaxHp(), enemy->getCurHp()),
                     &(dungeon.getMapLevel()[enemy->getCoords().second][enemy->getCoords().first])});
            (--dungeon.getListEnemies().end())->first->setHeap(true);
            (--dungeon.getListEnemies().end())->first->setFaction(enemy->getFaction());
            enemy->die();
            enemy->methodAfterDie(dungeon);
            dungeon.getHero().first->getCharacteristics().mana(manaCost * skillLvl / 2);
        }

        return 0;
    }

};


#endif //GAMELAB3_MORPHISM_H
