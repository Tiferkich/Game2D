//
// Created by sakhd on 23.10.2023.
//

#ifndef GAMELAB3_GAME_H
#define GAMELAB3_GAME_H

#include "../Unit/Character/Character.h"
#include "../Dungeon/Dungeon.h"
#include "../Unit/Enemy/LivingEnemy/LivingEnemy.h"
#include <list>
#include <utility>


///@brief Основной класс, связывающий все в одно целое
///Основной метод: \code   int makeTick(int options[] = nullptr); \endcode позволяющий сделать один тик в игре
class Game {
public:
    static std::vector<std::string> allTypesEnemies;///< Типы все врагов(при добавлении нового врага, следует сюда добавить его имя,но это необязательно)
    static std::vector<std::string> allSkills;
    static int option[12][2];///< Типы всех скиилов (такая же ситуция, как и с врагами)
private:

    Character hero; ///< Объект героя
    std::vector<Dungeon> allMap; ///< Массив уровней
    unsigned int curLvl = 0; ///< Текущий уровень
    unsigned int maxLvl = 2;
    TableSkills tableSkills; ///< Таблица скиллов персонажа
public:
    ///Дефолтный конструктор
    explicit Game() : curLvl(0), tableSkills(TableSkills()), hero(Character(10, {10, 20}, {5, 5}, &tableSkills)) {}

    unsigned int getMaxLvl() const;

    static void setAllTypesEnemies(const std::vector<std::string> &allTypesEnemies);

    static void setAllSkills(const std::vector<std::string> &allSkills);

    void setMaxLvl(unsigned int maxLvl);

    /** Основной метод позволяющий сделать один тик в игре
     * \param options опции для вызова какого то действия для игрока
     * \code
     *switch (options[0]) {
     *  case 1:
     *      move(Move::right, game.getAllMap()[getLvlPoint()]);
     *      break;
     *  case 2:
     *      move(Move::left, game.getAllMap()[getLvlPoint()]);
     *      break;
     *  case 3:
     *      move(Move::up, game.getAllMap()[getLvlPoint()]);
     *      break;
     * ... И так далее...
     * \endcode
     * \return int
     */
    int makeTick(int options[] = nullptr);

    /// Setter
    /// \param allMap все карты в игре
    void setAllMap(const std::vector<Dungeon> &allMap);

    /// Getter
    /// \return get hero
    Character &getHero();

    /// Getter
    /// \return get all map
    std::vector<Dungeon> &getAllMap();

    /// Getter
    /// \return get cur lvl
    unsigned int getCurLvl();

    /// Getter
    /// \return getTable of skills
    const TableSkills &getTableSkills() const;

    /// Setter
    /// \param hero set Hero
    void setHero(const Character &hero);

    /// Setter
    /// \param curLvl set cur lvl
    void setCurLvl(unsigned int curLvl);

    /// Setter
    /// \param tableSkills set table skills
    void setTableSkills(const TableSkills &tableSkills);


};


#endif //GAMELAB3_GAME_H
