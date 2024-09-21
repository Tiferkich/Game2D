//
// Created by sakhd on 18.11.2023.
//

#ifndef GAMELAB3_DESICCATION_H
#define GAMELAB3_DESICCATION_H

#include "../Skills.h"
#include "../../../../Dungeon/Dungeon.h"

///Иссушение позволяет превратить труп врага в ману или здоровье, получаемое количество зависитот характеристик
///врага и изученности навыка.
class Desiccation : public Skill {
public:
    ///Контсруктор
    explicit Desiccation() : Skill(0) {};
    /// Использовать скилл
    /// \param dungeon - уровень
    /// \param mas - опции
    /// \return 0 успех
    int useSkill(Dungeon &dungeon, int mas[]) override {
        if (skillLvl == 0) return -3;
        int y = dungeon.getHero().first->getCoords().first;
        int x = dungeon.getHero().first->getCoords().second;
        Enemy *enemy = nullptr;
        auto item = dungeon.getListEnemies().begin();
        for (item = dungeon.getListEnemies().begin(); item != dungeon.getListEnemies().end(); ++item) {
            if (item->first->getCoords().second == x && item->first->getCoords().first == y &&
                item->first->getStatus() == Status::dead && item->first->getFaction() == Faction::livingEnemy) {
                enemy = item->first;
                break;
            }
        }
        if (enemy == nullptr) return -2;
        if (dungeon.getHero().first->getCharacteristics().getCurHp() <
            dungeon.getHero().first->getCharacteristics().getCurMana()) {
            dungeon.getHero().first->getCharacteristics().health(enemy->getMaxHp() * skillLvl / 2);
        } else {
            dungeon.getHero().first->getCharacteristics().mana(enemy->getMaxHp() * skillLvl / 2);
        }
        enemy->setFaction(Faction::undead);
        enemy->methodAfterDie(dungeon);
        return 0;
    }

};


#endif //GAMELAB3_DESICCATION_H
