//
// Created by sakhd on 23.10.2023.
//

#include "../../../Dungeon/Ceil.h"

#ifndef GAMELAB3_GOLEM_H
#define GAMELAB3_GOLEM_H

#include "../Enemy.h"


#define VISION_GOLEM 5


///Каждый голем может с некоторой
///вероятностью проигнорировать урон, а после своей смерти (в зависимости от вида) оставляют либо
///стену(каменный), либо лаву(огиенный), либо эссенцию(фирный)
class Golem : public Enemy {
private:
    int hitPercentage;///< Процент попадания по голему
    Ceil ceil;///< Ячейка, на которую голем заменит по его коордам
public:
    Golem(int speed0, std::pair<int, int> damage0, std::pair<int, int> coord0, int maxHP, int hitPercentage0,
          Ceil ceil0)
            : Enemy(Faction::golem, speed0, damage0, coord0, "golem",
                    maxHP, maxHP, Status::wandering, VISION_GOLEM), hitPercentage(hitPercentage0),
              ceil(ceil0) {};

    /// Перегруженный метод получения урона, у голема есть шанс заблокировать урон
    /// \param damage - дамаг
    void getDamage(int damage) override;

    /// Перегруженный метод : "После смерти", оставит ячейку по его коордам
    /// \param dungeon - уровень
    void methodAfterDie(Dungeon &dungeon) override;

    /// Getter
    /// \return  hitPercentage
    int getHitPercentage() const {
        return hitPercentage;
    }

    /// Getter
    /// \return  ceil
    Ceil getCeil() const {
        return ceil;
    }

    /// Setter
    /// \param hitPercentage
    Golem &setHitPercentage(int hitPercentage) {
        Golem::hitPercentage = hitPercentage;
        return *this;
    }

    /// Setter
    /// \param ceil
    Golem &setCeil(Ceil ceil) {
        Golem::ceil = ceil;
        return *this;
    }

    /// Getter
    /// \return simpleGolem
    Enemies getType() override {
        return Enemies::simpleGolem;
    }


};


#endif //GAMELAB3_GOLEM_H
