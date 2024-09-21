//
// Created by sakhd on 26.10.2023.
//

#include <utility>


#ifndef GAMELAB3_UNDEADSUMMONER_H
#define GAMELAB3_UNDEADSUMMONER_H


#include "Isummoner.h"


class UndeadSummoner : public Isummoner, public Undead {
public:
    UndeadSummoner(int speed0, std::pair<int, int> damage0, std::pair<int, int> coord0,
                   int maxHP,
                   int curHP) : Undead(speed0, damage0, coord0, "undeadSummoner",
                                       "livingSummoner", maxHP,
                                       curHP), Isummoner(maxHP) {};



    ///  Перегруженный метод сделать что то, перегружен он потому что, саммонер умеет призывать
    /// \param matrix - уровень
    void doSomething(Dungeon &dungeon) override;
    /// Getter
    /// \return  livingSummoner
    Enemies getType() override {
        return Enemies::undeadSummoner;
    }

};


#endif //GAMELAB3_UNDEADSUMMONER_H
