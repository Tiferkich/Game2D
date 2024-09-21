//
// Created by sakhd on 23.10.2023.
//

#include <utility>


#ifndef GAMELAB3_LIVINGENEMY_H
#define GAMELAB3_LIVINGENEMY_H

#include "../Enemy.h"

#define VISION_LIVING 10

/// Живые противники оставляют после своейсмерти
///пригодное для дальнейшего использования тело
class LivingEnemy : public Enemy {
public:

    LivingEnemy(int speed0, std::pair<int, int> damage0, std::pair<int, int> coord0, std::string name, int maxHP,
                int curHP) : Enemy(
            Faction::livingEnemy, speed0, damage0, coord0, std::move(name), maxHP, curHP, Status::wandering,
            VISION_LIVING) {};

    LivingEnemy(int speed0, std::pair<int, int> damage0, std::pair<int, int> coord0, int maxHP,
                int curHP) : Enemy(
            Faction::livingEnemy, speed0, damage0, coord0, "livingEnemy", maxHP, curHP, Status::wandering,
            VISION_LIVING) {};

    /// Метод желательно должен быть перегружен у наследников
    /// Он удаляет с карты живого врага, и вместо него ставит нежить, которая соответсвует ему
    /// \param dungeon - Уровень
    virtual void becomeUndead(Dungeon &dungeon);

    /// Метод после смерти, опять же может быть перегружен, если враг будет умирать как то по-другому
    /// В данном случае он не удаляет с карты труп врага
    /// \param dungeon
    void methodAfterDie(Dungeon &dungeon) override;

    /// Getter
    /// \return тип
    Enemies getType() override {
        return Enemies::simpleLivingEnemy;
    }


};


#endif //GAMELAB3_LIVINGENEMY_H
