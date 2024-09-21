//
// Created by sakhd on 23.10.2023.
//


#ifndef GAMELAB3_CHARACTER_H
#define GAMELAB3_CHARACTER_H

#include "../Unit.h"
#include "../Enemy/Enemy.h"
#include "../../Dungeon/Ceil.h"
#include "../../Matrix/Matrix.h"
#include <map>
#include <list>
#include <iostream>
#include "TableSkills.h"


#define EXPERIENCE_COEFFICIENT 50
#define TAKE_ESSENCE 50

class Enemy;

///Структура характеристик персонажа
struct Characteristics {
private:
    int curHP;///< Текущее здоровье
    int maxHp;///< Максимальное здоровье
    int curMana;///< Текущая мана
    int maxMana;///< Максимальная мана
public:
    ///Дефолтный конструктор
    Characteristics() : curHP(100), maxHp(100), curMana(100), maxMana(100) {};

    /// \param maxHP0 - Хп
    /// \param maxMana0 - Мана
    [[maybe_unused]] Characteristics(int maxHP0, int maxMana0) : curHP(maxHP0), maxHp(maxHP0), curMana(maxMana0),
                                                                 maxMana(maxMana0) {};

    /// Метод лечения персонажа (или нет если подать -hp)
    /// \param hp - Кол-во здоровья на которое нужно изменить текущее
    /// \return *this - для цепного вызова
    Characteristics &health(int hp) {
        curHP = (curHP + hp);
        if (curHP < 0) curHP = 0;
        if (curHP > maxHp) curHP = maxHp;
        return *this;
    }
    /// Метод "лечения" персонажа (или нет если подать -mana)
    /// \param mana - Кол-во маны на которое нужно изменить текущее
    /// \return *this - для цепного вызова

    Characteristics &mana(int mana) {
        curMana = (curMana + mana);
        if (curMana < 0) curMana = 0;
        if (curMana > maxMana) curMana = maxMana;
        return *this;
    }

    /// Getter
    /// \return - Текущее здоровье
    int getCurHp() const {
        return curHP;
    }
    /// Getter
    /// \return - Максимальное здоровье

    int getMaxHp() const {
        return maxHp;
    }

    /// Getter
    /// \return - Текущая мана
    int getCurMana() const {
        return curMana;
    }

    /// Getter
    /// \return - Максимальная мана
    int getMaxMana() const {
        return maxMana;
    }

    /// Setter
    /// \param curHp0 - curHp
    Characteristics &setCurHp(int curHp0) {
        curHP = curHp0;
        return *this;
    }
    /// Setter
    /// \param maxHp0 - maxHp

    Characteristics &setMaxHp(int maxHp0) {
        Characteristics::maxHp = maxHp0;
        return *this;
    }

    /// Setter
    /// \param curMana0 - CurMana
    Characteristics &setCurMana(int curMana0) {
        Characteristics::curMana = curMana0;
        return *this;
    }

    /// Setter
    /// \param maxMana0 - MaxMana
    Characteristics &setMaxMana(int maxMana0) {
        Characteristics::maxMana = maxMana0;
        return *this;
    }

};


///Набор возможных состояний персонажа (Куда он смотрит)
enum class Move {
    right,
    left,
    up,
    down,
};

class Game;

///@brief Персонаж, которым мы играем
///Один из основных классов в игре, наследуется от юнита
class Character : public Unit {
private:
    int exp; ///<Кол-во экспы
    int lvl;///< Текущий уровень персонажа
    Characteristics characteristics;///< Его хар-ки
    TableSkills *tableSkills = nullptr;///< Указатель на таблицу скиллов
    int countEssence;///< Кол-во собранной эссенции
    Move sideLooking;///< Сторона куда смотрит персонаж
    int lvlPoint = 0;///< Кол-во доступных поинтов прокчки скилла
    std::vector<std::string> openEnemies;///< Вектор открытых персонажей
public:

    /// Контруктор для героя
    /// \param speed0 - Скорость
    /// \param damage0 - Дамаг мин и макс
    /// \param coord0 - Координаты х и у
    /// \param tableSkills - Указатель на таблицу скиллов
    Character(int speed0, std::pair<int, int> damage0, std::pair<int, int> coord0, TableSkills *tableSkills) : Unit(
            Faction::character, speed0,
            damage0, coord0),
                                                                                                               exp(0),
                                                                                                               lvl(1),
                                                                                                               countEssence(
                                                                                                                       0),
                                                                                                               sideLooking(
                                                                                                                       Move::right),
                                                                                                               tableSkills(
                                                                                                                       tableSkills) {};

    /// Getter
    /// \return Вектор открытых врагов
    const std::vector<std::string> &getOpenEnemies() const;

    /// Getter
    /// \return Вектор открытых врагов
    std::vector<std::string> &getOpenEnemies();

    /// Основной метод героя
    /// \param options - опции, что сделать
    /// \param game - ссылка на игру
    /// \return 0 - успех
    int doSomething(int options[], Game &game);

    /// Метод использования скилла
    /// \param nameSkill - название скилла
    /// \param dungeon - Ссылка на карту
    /// \param mas - Массив опций, mas[0] - выбрать какой скилл использовать, дальше иногда есть опции в скиллах
    /// \return 0 - успех
    int useSkill(const std::string &nameSkill, Dungeon &dungeon, int mas[] = {});

    /// Закрыть дверь на карте
    /// \param matrix - карта
    /// \return открытая дверь
    Ceil close(Matrix<Ceil> &matrix);

    /// Открыть дверь на карте
    /// \param matrix - карта
    /// \return закрытая дверь
    Ceil open(Matrix<Ceil> &matrix);

    ///Апнуть уровень
    void upLVL();

    /// Метод поиска рядом враг или нет
    /// \param coords  - координаты на проверку
    /// \return false - не рядом, true - рядом
    bool checkNear(std::pair<int, int> coords);


    /// При убийстве врага, вызывается этот метод, учеличивает экспу
    /// \param exp0 - Кол-во экспы
    void increaseExp(int exp0);

    ///  Посчитать кол-во поднятой нежити
    /// \param dungeon - уровень
    /// \return - 0 успех
    static int getCountSummons(Dungeon &dungeon);

    ///  Изучить врага
    /// \param dungeon - уровень
    /// \return 0 успех
    int openEnemy(Dungeon &dungeon);

    /// Проверка открыт ли враг или нет
    /// \param name - имя врага
    /// \return true - открыт
    bool isOpenEnemy(const std::string &name);

    /// Подняться или спуститься по лестнице
    /// \param matrix - карта
    /// \return  - true - можно
    bool uptoNewDungeon(Matrix<Ceil> &matrix, Matrix<Ceil> &matrixNew);

    /// Поиск ближайшего врага и атака его, вызывает метод attack(Unit &someone)
    /// \param dungeon - уровень
    /// \return  - 0 успех
    int attackSomeone(Dungeon &dungeon);

    /// Атака врага
    void attack(Unit &someone) override;

    /// Передвинуться по карте
    /// \param side - куда
    /// \param dungeon - карта
    /// \return 0 - успех
    int move(Move side, Dungeon &dungeon);

    /// Поднять эссенцию
    /// \param dungeon  - уровень
    /// \return 0 успех
    int takeEssense(Dungeon &dungeon);

    void die() override {};

    /// Получить урон (это не геттер)
    /// \param damage - урон
    void getDamage(int damage) override;

    /// Getter
    /// \return exp
    int getExp() const {
        return exp;
    }

    /// Getter
    /// \return curLvl
    int getLvl() const {
        return lvl;
    }

    /// Getter
    /// \return Characteristics
    Characteristics &getCharacteristics() {
        return characteristics;
    }

    /// Getter
    /// \return countEssence
    int getCountEssence() const {
        return countEssence;
    }

    /// Setter
    /// \param exp0 -newExp
    Character &setExp(int exp0) {
        Character::exp = exp0;
        return *this;
    }

    /// Setter
    /// \param lvl0 - newLvl

    Character &setLvl(int lvl0) {
        Character::lvl = lvl0;
        return *this;
    }

    /// Setter
    /// \param characteristics0 - new characteristics
    Character &setCharacteristics(const Characteristics &characteristics0) {
        Character::characteristics = characteristics0;
        return *this;
    }

    /// Setter
    /// \param countEssence0 - кол-во новой эссенции
    Character &setCountEssence(int countEssence0) {
        Character::countEssence = countEssence0;
        return *this;
    }
    /// Getter
    /// \return сторона куда смотрит

    Move getSideLooking() const;


    /// Setter
    /// \param sideLooking - новая сторона куда смотрит
    void setSideLooking(Move sideLooking);

    /// Getter
    /// \return - кол-во доступных поинтов улучшения скилла
    int getLvlPoint() const;

    /// Setter
    /// \param lvlPoint
    void setLvlPoint(int lvlPoint);

    /// Getter
    /// \return - Таблица скиллов
    TableSkills &getTableSkills();

    /// Setter
    /// \param tableSkills - Новая таблица скиллов
    void setTableSkills(TableSkills *tableSkills);

    /// Улучшить скилл
    /// \param skillName - название скилла
    /// \return 0 успех
    int upgradeSkill(const std::string &skillName);

    /// Метод который определяет - координаты подходят под условие куда смотрит герой или нет
    /// \param bx - x
    /// \param by - y
    /// \return - true - подходят
    bool check(int bx, int by) {
        if (sideLooking == Move::right) {
            if (coords.first <= bx) return true;
        } else if (sideLooking == Move::left) {
            if (coords.first >= bx) return true;
        } else if (sideLooking == Move::up) {
            if (coords.second >= by) return true;
        } else if (sideLooking == Move::down) { if (coords.second <= by) return true; }
        return false;
    }
};


#endif //GAMELAB3_CHARACTER_H
