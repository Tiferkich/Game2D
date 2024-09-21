//
// Created by sakhd on 24.10.2023.
//
#include <iostream>
#include <utility>

#include "../Unit.h"

#include "../../Dungeon/Ceil.h"

#include "../../Matrix/Matrix.h"


#ifndef GAMELAB3_ENEMY_H
#define GAMELAB3_ENEMY_H

#include <list>

#include "typiesOfEnemies.h"


class Dungeon;

/// Набор возможных состояний врага
enum class Status {
    wandering,
    aggresion,
    dead
};

enum class SideLooking {
    right,
    left,
    up,
    down,
};

///Расширяемый класс - враг
class Enemy : public Unit {
protected:
    int cost = 100; ///< Цена изучения врага
    std::string name; ///< Имя врага
    int maxHP; ///< Максимальное здоровье врага
    int curHP; ///< Текущее здоровье
    Status status;///< Статус врага
    int vision = 5;///< Зрение врага
    bool heap = false;///<	Создан на куче или нет
    SideLooking sideLooking = SideLooking::right;
public:
    /// Конструктор
    Enemy(Faction faction0, int speed0, std::pair<int, int> damage0, std::pair<int, int> coord0, std::string name,
          int maxHP, int curHP,
          Status status0, int vision0) : Unit(faction0, speed0, damage0, coord0), name(std::move(name)), maxHP(maxHP),
                                         curHP(curHP),
                                         status(status0), vision(vision0) {};

    /// Метод передвижения врага по карте
    /// \param matrix - карта
    /// \param coordTo - куда ему идти
    /// \param listEnemies - список врагов
    void move(Matrix<Ceil> &matrix, std::pair<int, int> coordTo);

    SideLooking getSideLooking() const;

    /// Атакавать кого то
    /// \param someone - Кто-то
    void attack(Unit &someone) override;

    /// Получить урон (Это не геттер)
    /// \param damage - урон
    void getDamage(int damage) override;

    ///Смерть, статус меняется на dead и текущее хп на 0
    void die() override {
        status = Status::dead;
        speed = 0;
        curHP = 0;
    }

    /// Получить тип
    /// \return тип
    virtual Enemies getType() {
        return Enemies::simpleEnemy;
    }

    /// Цена открытия для изучения персонажем
    /// \return cost
    virtual int openCost() {
        return cost;
    }

    ///Установить true или false
    void setHeap(bool heap);

    bool isHeap() const;

    /// Метод после смерти, он перегружен для големов и живых(големы оставляют на карте что-то, живые оставляют труп), а по дефолту просто удаляет врага
    /// \param dungeon - уровень
    virtual void methodAfterDie(Dungeon &dungeon);

    ///Метод сделать - что-то, объединяет все действия врага и выполняет их, если враг делает что то необычное его нужно перегрузить
    ///Например саммонер призывает врагов, поэтому этот метод в нем перегружен
    virtual void doSomething(Dungeon &);

    /// Getter
    /// \return имя
    const std::string &getName() const {
        return name;
    }

    /// Getter
    /// \return vision
    int getVision() const {
        return vision;
    }

    /// Getter
    /// \return maxHP
    int getMaxHp() const {
        return maxHP;
    }

    /// Getter
    /// \return curHP
    int getCurHp() const {
        return curHP;
    }

    /// Getter
    /// \return status
    Status getStatus() {
        return status;
    }

    /// Setter
    /// \param vision0  - vision
    Enemy &setVision(int vision0) {
        vision = vision0;
        return *this;
    }

    /// Setter
    /// \param name0 - name
    Enemy &setName(const std::string &name0) {
        Enemy::name = name0;
        return *this;
    }

    /// Setter
    /// \param maxHp - maxHP
    Enemy &setMaxHp(int maxHp) {
        maxHP = maxHp;
        return *this;
    }

    /// Setter
    /// \param curHp - curHP
    Enemy &setCurHp(int curHp) {
        curHP = curHp;
        return *this;
    }

    /// Setter
    /// \param status0 - status
    Enemy &setStatus(Status status0) {
        Enemy::status = status0;
        return *this;
    }

    /// Найти цель, ищет юнита до которого можно добраться
    /// \param dungeon - уровень
    /// \return Юнита
    Unit *findTarget(Dungeon &dungeon);
    /// Алгоритм Ли, используется для поиска пути до координат
    /// \param matrix - карта
    /// \param coordTo - координаты куда нужно идти
    /// \return возвращает вектор путей

private:
    std::vector<std::pair<int, int>> Lee(Matrix<Ceil> &matrix, std::pair<int, int> coordTo);
};


#endif //GAMELAB3_ENEMY_H
