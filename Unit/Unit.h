//
// Created by sakhd on 23.10.2023.
//

#include <iostream>
#include <utility>


#ifndef GAMELAB3_UNIT_H
#define GAMELAB3_UNIT_H

///Набор возможных состояний юнита
enum class Faction {
    character,///< Юнит сражается за сторону героя
    undead,///< Фракция нежити
    livingEnemy,///< Фракция живых существ
    golem,///<Фракция големов
};


///Абстрактный класс - юнит, от него наследуется Character и Enemy
class Unit {
protected:
    Faction faction;///<Фракция юнита
    unsigned int speed;///<Скорость юнита (нигде не использовалось, но может быть будет)
    std::pair<int, int> damage;///< Дамаг юнита, damage.first - минимальный дамаг, damage.second - максимальный дамаг
    std::pair<int, int> coords;///< Координаты x,y
public:
    /// @brief Конструктор
    /// \param faction0 -  Фракция юнита
    /// \param speed0  - Скорость юнита
    /// \param damage0 - Дамаг юнита, damage.first - минимальный дамаг, damage.second - максимальный дамаг
    /// \param coord0 - Координаты x,y
    Unit(Faction faction0, int speed0, std::pair<int, int> damage0, std::pair<int, int> coord0) : faction(faction0),
                                                                                                  speed(speed0),
                                                                                                  damage(damage0),
                                                                                                  coords(std::move(
                                                                                                          coord0)) {};
    ///Чисто виртуальный метод - смерти
    virtual void die() = 0;
    ///Чисто виртуальный метод - атаки кого то
    virtual void attack(Unit &someone) = 0;

    ///Чисто виртуальный метод - получения урона (это не геттер)
    virtual void getDamage(int damage) = 0;


    /// Getter
    /// \return - возвращает фракцию юнита
    Faction getFaction() const {
        return faction;
    }
    /// Getter
    /// \return - возвращает скорость юнита

    int getSpeed() const {
        return speed;
    }

    /// Getter
    /// \return - возвращает урон юнита

    std::pair<int, int> Damage() const {
        return damage;
    }

    /// Getter
    /// \return - возвращает координаты юнита

    const std::pair<int, int> &getCoords() const {
        return coords;
    }

    /// Setter
    /// \param faction0 - Фракция
    /// \return возвращает ссылку на класс для цепного вызова

    Unit &setFaction(Faction faction0) {
        Unit::faction = faction0;
        return *this;
    }
    /// Setter
    /// \param speed0 - Скорость юнита
    /// \return  возвращает ссылку на класс для цепного вызова

    Unit &setSpeed(int speed0) {
        Unit::speed = speed0;
        return *this;
    }
    /// Setter
    /// \param damage0 - урон юнита

    void setDamage(std::pair<int, int> damage0) {
        Unit::damage = damage0;
    }

    ///Setter
    /// \param coords0 - Координаты юнита

    Unit &setCoords(const std::pair<int, int> &coords0) {
        Unit::coords = coords0;
        return *this;
    }
};


#endif //GAMELAB3_UNIT_H
