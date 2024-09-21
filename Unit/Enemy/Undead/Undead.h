//
// Created by sakhd on 23.10.2023.
//

#include <iostream>
#include <utility>
#include "../Enemy.h"

#ifndef GAMELAB3_UNDEAD_H
#define GAMELAB3_UNDEAD_H

#define VISION_UNDEAD 10

///Нежить, при смерти очищается с карты, ничего не делая
class Undead : public Enemy {
protected:
    std::string nameLiving;///< Имя при жизни, оно должно соответсвовать какому-то, реально существующему имени
public:
    Undead(int speed0, std::pair<int, int> damage0, std::pair<int, int> coord0, std::string name,
           std::string nameLiving0, int maxHP,
           int curHP) : Enemy(
            Faction::undead, speed0, damage0, coord0, std::move(name), maxHP, curHP, Status::wandering, VISION_UNDEAD),
                        nameLiving(std::move(nameLiving0)) {};

    Undead(int speed0, std::pair<int, int> damage0, std::pair<int, int> coord0, int maxHP,
           int curHP) : Enemy(
            Faction::undead, speed0, damage0, coord0, "undead", maxHP, curHP, Status::wandering, VISION_UNDEAD),
                        nameLiving("livingEnemy") {};
    /// Getter
    /// \return получить имя при жизни
    const std::string &getNameLiving() const {
        return nameLiving;
    }
    /// Setter
    /// \param nameLiving - имя при жизни
    void setNameLiving(const std::string &nameLiving) {
        Undead::nameLiving = nameLiving;
    }
    /// Getter в итоге нигде не использовался
    /// \return Вернет фракцию - simpleUndeadEnemy
    Enemies getType() override {
        return Enemies::simpleUndeadEnemy;
    }

};


#endif //GAMELAB3_UNDEAD_H
