//
// Created by sakhd on 26.10.2023.
//

#include <utility>


#ifndef GAMELAB3_LIVINGSUMMONER_H
#define GAMELAB3_LIVINGSUMMONER_H

#include "../LivingEnemy/LivingEnemy.h"
#include "../Undead/Undead.h"
#include "../../../Dungeon/Dungeon.h"
#include "Isummoner.h"

///Живой саммонер, наследуется от живого врага  и от саммонера
class LivingSummoner : public LivingEnemy, public Isummoner {
private:
    int cost = 500;///<Цена открытия
public:
    LivingSummoner(int speed0, std::pair<int, int> damage0, std::pair<int, int> coord0, int maxHP) : LivingEnemy(speed0,
                                                                                                                 damage0,
                                                                                                                 coord0,
                                                                                                                 "livingSummoner",
                                                                                                                 maxHP,
                                                                                                                 maxHP),
                                                                                                     Isummoner(maxHP) {};
    /// Перегруженный метод, превращает живого саммонера в нежить саммонера
    /// \param dungeon - уровен
    void becomeUndead(Dungeon &dungeon) override;
    /// Цена открытия
    /// \return  cost
    int openCost() override {
        return cost;
    }



    ///  Перегруженный метод сделать что то, перегружен он потому что, саммонер умеет призывать
    /// \param matrix - уровень
    void doSomething(Dungeon &matrix) override;
    /// Getter
    /// \return  livingSummoner
    Enemies getType() override {
        return Enemies::livingSummoner;
    }


};


#endif //GAMELAB3_LIVINGSUMMONER_H
