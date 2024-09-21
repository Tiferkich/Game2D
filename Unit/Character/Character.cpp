//
// Created by sakhd on 23.10.2023.
//

#include "Character.h"
#include "../../Dungeon/Dungeon.h"
#include "../Enemy/Undead/Undead.h"
#include "../Enemy/Summoner/UndeadSummoner.h"
#include "../../Game/Game.cpp"


int Character::upgradeSkill(const std::string &skillName) {
    if (lvlPoint == 0) {
        return -1;
    }
    lvlPoint -= 1;
    tableSkills->upgradeSkill(skillName);
    return 0;
}


void Character::increaseExp(int exp0) {
    exp += exp0;
    if (exp >= EXPERIENCE_COEFFICIENT * lvl) upLVL();
}


void Character::attack(Unit &someone) {
    if (dynamic_cast<Enemy *> (&someone)->getStatus() == Status::dead) {
        throw (std::invalid_argument("Unit is dead"));
    }
    if (!checkNear(someone.getCoords())) {
        throw (std::invalid_argument("Unit too far away"));
    }
    int damage0 = rand() % (damage.second - damage.first + 1) + damage.first;
    someone.getDamage(damage0);
    if (dynamic_cast<Enemy *> (&someone)->getStatus() == Status::dead)
        increaseExp(dynamic_cast<Enemy *> (&someone)->getMaxHp() / 2);
}

void Character::upLVL() {
    exp = 0;
    lvl += 1;
    lvlPoint += 1;
    characteristics.setMaxHp(characteristics.getMaxHp() + 50);
    characteristics.setMaxMana(characteristics.getMaxMana() + 50);
    damage.first += 7;
    damage.second += 7;
}

void Character::getDamage(int damage) {
    characteristics.health(-1 * damage);
    if (characteristics.getCurHp() <= 0) {
        die();
    }
}

int Character::takeEssense(Dungeon &dungeon) {
    if (dungeon.getMapLevel()[coords.first][coords.second] != Ceil::essence)
        return -1;
    countEssence += TAKE_ESSENCE;
    dungeon.getMapLevel()[coords.first][coords.second] = Ceil::floor;
    return 0;
}


int Character::move(Move side, Dungeon &dungeon) {
    sideLooking = side;
    if (side == Move::down && dungeon.getMapLevel()[coords.first + 1][coords.second] != Ceil::wall &&
        dungeon.getMapLevel()[coords.first + 1][coords.second] != Ceil::closeDoor) {
        ++coords.first;
    } else if (side == Move::up && dungeon.getMapLevel()[coords.first - 1][coords.second] != Ceil::wall &&
               dungeon.getMapLevel()[coords.first - 1][coords.second] != Ceil::closeDoor) {
        --coords.first;
    } else if (side == Move::right && dungeon.getMapLevel()[coords.first][coords.second + 1] != Ceil::wall &&
               dungeon.getMapLevel()[coords.first][coords.second + 1] != Ceil::closeDoor) {
        ++coords.second;
    } else if (side == Move::left && dungeon.getMapLevel()[coords.first][coords.second - 1] != Ceil::wall &&
               dungeon.getMapLevel()[coords.first][coords.second - 1] != Ceil::closeDoor) {
        --coords.second;
    } else {
        return -1;
    }
    dungeon.setHero({this, &dungeon.getMapLevel()[coords.first][coords.second]});
    return 0;
}


Ceil Character::close(Matrix<Ceil> &matrix) {
    bool flag = false;
    int dx[9] = {1, 0, -1, 0, 1, 0, 1, -1, -1};   // смещения, соответствующие соседям ячейки
    int dy[9] = {0, 1, 0, -1, 1, 0, -1, -1, 1};
    int x, y;
    for (int i = 0; i < 6; i++) {
        if (flag) { break; }
        x = coords.second + dx[i];
        y = coords.first + dy[i];
        if (matrix[y][x] == Ceil::openDoor) flag = true;
    }
    if (!flag) throw std::invalid_argument("No open door");
    matrix[y][x] = Ceil::closeDoor;
    return Ceil::openDoor;
}


Ceil Character::open(Matrix<Ceil> &matrix) {
    bool flag = false;
    int dx[9] = {1, 0, -1, 0, 1, 0, 1, -1, -1};   // смещения, соответствующие соседям ячейки
    int dy[9] = {0, 1, 0, -1, 1, 0, -1, -1, 1};
    int x, y;
    for (int i = 0; i < 6; i++) {
        if (flag) { break; }
        x = coords.second + dx[i];
        y = coords.first + dy[i];
        if (matrix[y][x] == Ceil::closeDoor) flag = true;
    }
    if (!flag) throw std::invalid_argument("No close door");
    matrix[y][x] = Ceil::openDoor;
    return Ceil::closeDoor;
}


bool Character::checkNear(std::pair<int, int> anotherCoords) {
    bool flag = false;
    int dx[9] = {1, 0, -1, 0, 1, 0, 1, -1, -1};   // смещения, соответствующие соседям ячейки
    int dy[9] = {0, 1, 0, -1, 1, 0, -1, -1, 1};
    for (int i = 0; i < 9; i++) {
        if (flag) { return true; }
        int x = coords.second + dx[i];
        int y = coords.first + dy[i];
        if (x == anotherCoords.second && y == anotherCoords.first) flag = true;
    }
    return false;
}

int Character::getLvlPoint() const {
    return lvlPoint;
}

void Character::setLvlPoint(int lvlPoint) {
    Character::lvlPoint = lvlPoint;
}

Move Character::getSideLooking() const {
    return sideLooking;
}

void Character::setSideLooking(Move sideLooking) {
    Character::sideLooking = sideLooking;
}

int Character::useSkill(const std::string &nameSkill, Dungeon &dungeon, int mas[]) {
    tableSkills->getSkill(nameSkill)->useSkill(dungeon, mas);
    return 0;
}

TableSkills &Character::getTableSkills() {
    return *tableSkills;
}

void Character::setTableSkills(TableSkills *tableSkills) {
    Character::tableSkills = tableSkills;
}

int Character::getCountSummons(Dungeon &dungeon) {
    int counter = 0;
    for (auto &item: dungeon.getListEnemies()) {
        if (item.first->getFaction() == Faction::character) ++counter;
    }
    return counter;
}

int Character::openEnemy(Dungeon &dungeon) {
    if (countEssence == 0) return -3;
    auto item = dungeon.getListEnemies().begin();
    Enemy *enemy = nullptr;
    for (item = dungeon.getListEnemies().begin(); item != dungeon.getListEnemies().end(); item++) {
        if (item->first->getStatus() == Status::dead && item->first->getFaction() == Faction::livingEnemy &&
            checkNear(item->first->getCoords()) && !isOpenEnemy(item->first->getName())) {
            enemy = item->first;
        }
    }
    if (enemy == nullptr) return -1;
    if (enemy->openCost() > countEssence) return -2;
    openEnemies.emplace_back(enemy->getName());
    countEssence -= enemy->openCost();
    return 0;
}

bool Character::isOpenEnemy(const std::string &name) {
    for (auto &item: openEnemies) {
        if (item == name) return true;
    }
    return false;
}

const std::vector<std::string> &Character::getOpenEnemies() const {
    return openEnemies;
}

std::vector<std::string> &Character::getOpenEnemies() {
    return openEnemies;
}


int Character::doSomething(int options[], Game &game) {
    if (game.getAllMap()[game.getCurLvl()].getMapLevel()[coords.first][coords.second] == Ceil::lava) {
        this->getDamage(50);
    }
    if (options == nullptr) return -1;
    switch (options[0]) {
        case 1:
            move(Move::right, game.getAllMap()[game.getCurLvl()]);
            break;
        case 2:
            move(Move::left, game.getAllMap()[game.getCurLvl()]);
            break;
        case 3:
            move(Move::up, game.getAllMap()[game.getCurLvl()]);
            break;
        case 4:
            move(Move::down, game.getAllMap()[game.getCurLvl()]);
            break;
        case 5:
            try {
                open(game.getAllMap()[game.getCurLvl()].getMapLevel());
                break;
            } catch (...) {
                break;
            }
        case 6:
            try {
                close(game.getAllMap()[game.getCurLvl()].getMapLevel());
                break;
            } catch (...) {
                break;
            }
        case 7:
            takeEssense(game.getAllMap()[game.getCurLvl()]);
            break;
        case 8: {
            if (game.getAllMap().size() > game.getCurLvl() + 1) {
                if (uptoNewDungeon(game.getAllMap()[game.getCurLvl()].getMapLevel(),
                                   game.getAllMap()[game.getCurLvl() + 1].getMapLevel()))
                    game.setCurLvl(game.getCurLvl() + 1);
            }
            break;
        }
        case 9: {
            if (game.getCurLvl() == 0) break;
            if (uptoNewDungeon(game.getAllMap()[game.getCurLvl()].getMapLevel(),
                               game.getAllMap()[game.getCurLvl() - 1].getMapLevel()))
                game.setCurLvl(game.getCurLvl() - 1);
            break;
        }
        case 10: {
            int forMorphism[] = {options[2]};
            useSkill(Game::allSkills[options[1]], game.getAllMap()[game.getCurLvl()], forMorphism);
            break;
        }
        case 11:
            upgradeSkill(Game::allSkills[options[1]]);
            break;
        case 12:
            attackSomeone(game.getAllMap()[game.getCurLvl()]);
            break;
    }
    return 0;
}

bool Character::uptoNewDungeon(Matrix<Ceil> &matrix, Matrix<Ceil> &matrixNew) {
    if (matrix[coords.first][coords.second] == Ceil::ladder && matrixNew[coords.first][coords.second] == Ceil::ladder)
        return true;
    return false;
}


int Character::attackSomeone(Dungeon &dungeon) {
    Enemy *enemy = nullptr;
    auto item = dungeon.getListEnemies().begin();
    for (item = dungeon.getListEnemies().begin(); item != dungeon.getListEnemies().end(); ++item) {
        if (check(item->first->getCoords().first,
                  item->first->getCoords().second) &&
            item->first->getStatus() != Status::dead && checkNear(item->first->getCoords())) {
            enemy = item->first;
        }
    }
    if (enemy == nullptr) {
        return -1;
    }
    attack(*enemy);
    return 0;
}






