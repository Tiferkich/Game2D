//
// Created by sakhd on 24.10.2023.
//

#include "Enemy.h"
#include "../../Dungeon/Dungeon.h"
#include "../Character/Character.h"


void Enemy::attack(Unit &someone) {
    if (status == Status::dead) throw (std::invalid_argument("Unit is dead"));
    if (someone.getFaction() == faction) {
        status = Status::wandering;
        throw (std::invalid_argument("The same unit"));
    }
    bool flag = false;
    int dx[9] = {1, 0, -1, 0, 1, 0, 1, -1, -1};   // смещения, соответствующие соседям ячейки
    int dy[9] = {0, 1, 0, -1, 1, 0, -1, -1, 1};
    for (int i = 0; i < 9; i++) {
        if (flag) { break; }
        int x = coords.second + dx[i];
        int y = coords.first + dy[i];
        if (x == someone.getCoords().second && y == someone.getCoords().first) flag = true;
    }

    if (!flag) {
        status = Status::wandering;
        return;
    }
    srand(time(0));
    int damage0 = rand() % (damage.second - damage.first + 1) + damage.first;
    status = Status::aggresion;
    someone.getDamage(damage0);
}

void Enemy::getDamage(int damage) {
    curHP -= damage;
    if (curHP <= 0) {
        die();
    }
}


std::vector<std::pair<int, int>> Enemy::Lee(Matrix<Ceil> &matrix, std::pair<int, int> coordTo) {
    //if (coordTo.first == coords.first && coordTo.second == coords.second)
    int W = matrix.cols();         // ширина рабочего поля
    int H = matrix.rows();         // высота рабочего поля
    int WALL = -1;                 // непроходимая ячейка
    int ax = coords.second;
    int ay = coords.first;
    int bx = coordTo.second;
    int by = coordTo.first;
    int BLANK = -2;                // свободная непомеченная ячейка
    int grid[matrix.rows()][matrix.cols()];
    for (int j = 0; j < matrix.cols(); j++) {
        for (int i = 0; i < matrix.rows(); i++) {
            if (matrix[i][j] == Ceil::wall || matrix[i][j] == Ceil::closeDoor) {
                grid[i][j] = WALL;
            } else {
                grid[i][j] = BLANK;
            }
        }
    }
    int dx[4] = {1, 0, -1, 0};   // смещения, соответствующие соседям ячейки
    int dy[4] = {0, 1, 0, -1};   // справа, снизу, слева и сверху
    int d, x, y, k;
    int len;
    int px[W * H], py[W * H];
    bool stop;

    if (grid[ay][ax] == WALL && grid[by][bx] == WALL)
        throw std::runtime_error("No way");  // ячейка (ax, ay) или (bx, by) - стена

    // распространение волны
    d = 0;
    grid[ay][ax] = 0;            // стартовая ячейка помечена 0
    do {
        stop = true;               // предполагаем, что все свободные клетки уже помечены
        for (y = 0; y < H; ++y)
            for (x = 0; x < W; ++x)
                if (grid[y][x] == d)                         // ячейка (x, y) помечена числом d
                {
                    for (k = 0; k < 4; ++k)                    // проходим по всем непомеченным соседям
                    {
                        int iy = y + dy[k], ix = x + dx[k];
                        if (iy >= 0 && iy < H && ix >= 0 && ix < W &&
                            grid[iy][ix] == BLANK) {
                            stop = false;              // найдены непомеченные клетки
                            grid[iy][ix] = d + 1;      // распространяем волну
                        }
                    }
                }
        d++;
    } while (!stop && grid[by][bx] == BLANK);

    if (grid[by][bx] == BLANK) throw (std::runtime_error("No way"));  // путь не найден

    // восстановление пути
    len = grid[by][bx];            // длина кратчайшего пути из (ax, ay) в (bx, by)
    x = bx;
    y = by;
    d = len;
    while (d > 0) {
        px[d] = x;
        py[d] = y;                   // записываем ячейку (x, y) в путь
        d--;
        for (k = 0; k < 4; ++k) {
            int iy = y + dy[k], ix = x + dx[k];
            if (iy >= 0 && iy < H && ix >= 0 && ix < W &&
                grid[iy][ix] == d) {
                x = x + dx[k];
                y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
                break;
            }
        }
    }
    px[0] = ax;
    py[0] = ay;
    std::vector<std::pair<int, int>> array;
    for (int i = 0; i < len; i++) {
        array.emplace_back(px[i], py[i]);
    }
    return array;
}

void
Enemy::move(Matrix<Ceil> &matrix, std::pair<int, int> coordTo) {

    if (coordTo.first < 0 || coordTo.second < 0 ||
        coordTo.second >= matrix.cols() ||
        coordTo.first >= matrix.rows())
        throw std::runtime_error("invalid coords");

    if ((coordTo.first - coords.first) * (coordTo.first - coords.first) +
        (coordTo.second - coords.second) * (coordTo.second - coords.second) > vision * vision * vision) {
        status = Status::wandering;
        throw std::invalid_argument("Error distance");
    }
    std::vector<std::pair<int, int>> ways = Lee(matrix, {coordTo.first, coordTo.second});
    if (ways.size() == 1 || ways.empty()) {
        return;
    }
    if (coords.second > ways[1].first) {
        sideLooking = SideLooking::left;
    }
    if (coords.second < ways[1].first){
        sideLooking = SideLooking::right;
    }
    coords.first = ways[1].second;
    coords.second = ways[1].first;

}


Unit *Enemy::findTarget(Dungeon &dungeon) {
    std::pair<int, int> nearDist = {INT32_MAX / 10, INT32_MAX / 10};
    Unit *unit = nullptr;
    auto enemy = dungeon.getListEnemies().begin();
    for (enemy = dungeon.getListEnemies().begin(); enemy != dungeon.getListEnemies().end(); ++enemy) {
        if ((enemy->first->getCoords().first - coords.first) * (enemy->first->getCoords().first - coords.first) +
            (enemy->first->getCoords().second - coords.second) * (enemy->first->getCoords().second - coords.second) <
            nearDist.first * nearDist.first + nearDist.second * nearDist.second &&
            enemy->first->status != Status::dead && enemy->first->faction != faction &&
            abs(enemy->first->getCoords().second - coords.second) +
            abs(enemy->first->getCoords().first - coords.first) <=
            vision) {
            nearDist.first = (enemy->first->getCoords().first - coords.first);
            nearDist.second = (enemy->first->getCoords().second - coords.second);
            unit = enemy->first;
        }
    }
    if ((dungeon.getHero().first->getCoords().first - coords.first) *
        (dungeon.getHero().first->getCoords().first - coords.first) +
        (dungeon.getHero().first->getCoords().second - coords.second) *
        (dungeon.getHero().first->getCoords().second - coords.second) <
        nearDist.first * nearDist.first + nearDist.second * nearDist.second &&
        dungeon.getHero().first->getFaction() != faction &&
        dungeon.getHero().first->getCharacteristics().getCurHp() > 0 &&
        abs(dungeon.getHero().first->getCoords().second - coords.second) +
        abs(dungeon.getHero().first->getCoords().first - coords.first) <= vision) {
        unit = dungeon.getHero().first;
    }


    return unit;
}


void Enemy::doSomething(Dungeon &dungeon) {
    if (status == Status::dead) {
        return;
    }
    Unit *someone = findTarget(dungeon);
    if (someone == nullptr) {
        status = Status::wandering;
        srand(time(0));
        int i = rand() % 4;
        int dx[4] = {1, -1, -1, 1};   // смещения, соответствующие соседям ячейки
        int dy[4] = {1, -1, 1, -1};
        if (coords.first + dy[i] < 0 || coords.second + dx[i] < 0 ||
            coords.second + dx[i] >= dungeon.getMapLevel().cols() ||
            coords.first + dy[i] >= dungeon.getMapLevel().rows())
            return;
        try {
            move(dungeon.getMapLevel(), {coords.first + dy[i], coords.second + dx[i]});
        } catch (...) {}
        return;
    } else {
        try {
            attack(*someone);
            move(dungeon.getMapLevel(), {someone->getCoords().first, someone->getCoords().second});
            status = Status::aggresion;
        } catch (...) {}
    }
}

void Enemy::methodAfterDie(Dungeon &dungeon) {
    if (status != Status::dead) throw (std::invalid_argument("Not dead enemy"));
    for (auto i = dungeon.getListEnemies().begin(); i != dungeon.getListEnemies().end(); i++) {
        try {
            if (i->first == this) {
                dungeon.getListEnemies().erase(i);
                break;
            }
        } catch (...) {}
    }
}

bool Enemy::isHeap() const {
    return heap;
}

void Enemy::setHeap(bool heap) {
    Enemy::heap = heap;
}

SideLooking Enemy::getSideLooking() const {
    return sideLooking;
}



