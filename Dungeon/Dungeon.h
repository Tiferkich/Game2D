//
// Created by sakhd on 23.10.2023.
//
#include <list>
#include <utility>
#include <vector>
#include <memory>


#ifndef GAMELAB3_DUNGEON_H
#define GAMELAB3_DUNGEON_H

#include "../Matrix/Matrix.h"
#include "Ceil.h"
#include "../Unit/Enemy/Enemy.h"
#include "../Unit/Unit.h"
#include "../Unit/Character/Character.h"
#include "../Unit/Enemy/Golem/Golem.h"


///Класс, который описывает поведение уровня игры(подземелья)
class Dungeon {
private:

    std::list<std::pair<Enemy *, Ceil *>> listEnemies; ///< Cписок врагов и их местоположение на карте
    Matrix<Ceil> mapLevel;///< Сам уровень
    int wigth;///<ширина(X)
    int height;///<высота(Y)
    std::pair<Character *, Ceil *> hero;///< Указатель на героя
public:
    ///
    /// \param list список врагов
    /// \param mapLevel0  карта
    /// \param wight0 ширина карты
    /// \param height0 высота карты
    /// \param hero0 указатель на героя
    Dungeon(std::list<std::pair<Enemy *, Ceil *>> list, Matrix<Ceil> &mapLevel0,
            int wight0,
            int height0, std::pair<Character *, Ceil *> hero0) : listEnemies(std::move(list)),
                                                                 mapLevel(mapLevel0),
                                                                 wigth(wight0),
                                                                 height(height0), hero(std::move(hero0)) {};


    ///@brief Основной метод подземелья
    ///В ней каждый враг совершает какое-либо действие, а также происходит чистка от мертвых врагов
    void allDoSomething();


    /// \brief Вспомогательная перегрузка оператора
    /// Нужен для добавления новых существ в данжион
    /// \param enemy враг

    Dungeon operator+=(std::pair<Enemy *, Ceil *> enemy) {
        listEnemies.emplace_back(enemy);
        return *this;
    }

    void printEnemies();

    void print();

    /// Getter
    /// \return Список врагов
    std::list<std::pair<Enemy *, Ceil *>> &getListEnemies() {
        return listEnemies;
    }
    /// Getter
    /// \return возвращает матрицу уровня

    Matrix<Ceil> &getMapLevel() {
        return mapLevel;
    }
    /// Getter
    /// \return возвращает  ширину

    int getWigth() const {
        return wigth;
    }
    /// Getter
    /// \return возвращает  высоту

    int getHeight() const {
        return height;
    }

    /// Getter
    /// \return возвращает  указатель на персонажа

    std::pair<Character *, Ceil *> &getHero() {
        return hero;
    }

    /// Setter
    /// \param hero Ссылка на героя

    void setHero(const std::pair<Character *, Ceil *> &hero) {
        Dungeon::hero = hero;
    };

    /// Setter
    /// \param listEnemies0 Список врагов
    /// \return возвращает ссылку на этот же данж, для цепного вызова

    Dungeon &setListEnemies(std::list<std::pair<Enemy *, Ceil *>> listEnemies0) {
        Dungeon::listEnemies = std::move(listEnemies0);
        return *this;
    }
    /// Setter
    /// \param mapLevel0 - Матрица уровня
    /// \return возвращает ссылку на этот же данж, для цепного вызова

    Dungeon &setMapLevel(Matrix<Ceil> &mapLevel0) {
        Dungeon::mapLevel = std::move(mapLevel0);
        return *this;
    }


    /// Setter
    /// \param wigth0 - ширина
    /// \return  возвращает ссылку на этот же данж, для цепного вызова
    Dungeon &setWigth(int wigth0) {
        Dungeon::wigth = wigth0;
        return *this;
    }

    /// Setter
    /// \param height0 - высота
    /// \return возвращает ссылку на этот же данж, для цепного вызова

    Dungeon &setHeight(int height0) {
        Dungeon::height = height0;
        return *this;
    }


};


#endif //GAMELAB3_DUNGEON_H
