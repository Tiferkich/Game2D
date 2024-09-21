//
// Created by sakhd on 23.10.2023.
//

#include "Dungeon.h"
#include "../Unit/Character/Character.h"


void Dungeon::allDoSomething() {
    for (auto &i: listEnemies) {
        try {
            i.first->doSomething(*this);
            if (mapLevel[i.first->getCoords().first][i.first->getCoords().second] == Ceil::lava) {
                i.first->getDamage(50);
            }
        } catch (...) {}
    }
    if (mapLevel[hero.first->getCoords().first][hero.first->getCoords().second] == Ceil::lava) {
        hero.first->getDamage(50);
    }
    int size = listEnemies.size();
    for (int i = 0; i < listEnemies.size() * 2; i++) {
        for (auto &listEnemie: this->listEnemies) {
            try {
                listEnemie.first->methodAfterDie(*this);
                if (size != listEnemies.size()) {
                    size = listEnemies.size();
                    break;
                }
            } catch (...) { continue; }

        }
    }
}

//void Dungeon::print() {
//    for (int i = 0; i < wigth; i++) {
//        std::cout << std::endl;
//        for (int j = 0; j < height; j++) {
//            for (auto &listEnemie: listEnemies) {
//                if (listEnemie.first->getCoords().first == i && listEnemie.first->getCoords().second == j) {
//                    std::cout << listEnemie.first->getName() << " ";
//                    ++j;
//                    break;
//                }
//            }
//            if (hero.first->getCoords().first == i && hero.first->getCoords().second == j) {
//                std::cout << "Hero ";
//                ++j;
//            }
//
//
//            if (j >= height) break;
//            if (mapLevel[i][j] == Ceil::openDoor) {
//                std::cout << "open ";
//                continue;
//            }
//            if (mapLevel[i][j] == Ceil::closeDoor) {
//                std::cout << "close ";
//                continue;
//            }
//            if (mapLevel[i][j] == Ceil::wall) {
//                std::cout << "walls ";
//            }
//            if (mapLevel[i][j] == Ceil::floor) {
//                std::cout << "floor ";
//                continue;
//            }
//            if (mapLevel[i][j] == Ceil::lava) {
//                std::cout << "lava ";
//                continue;
//            }
//            if (mapLevel[i][j] == Ceil::essence) {
//                std::cout << "essen ";
//                continue;
//            }
//        }
//    }
//    std::cout << std::endl;
//
//}
//
//void Dungeon::printEnemies() {
//    for (auto &i: listEnemies) {
//        std::cout << "name: " << i.first->getName() << " " << i.first->getCurHp() << "/" << i.first->getMaxHp()
//                  << std::endl;
//    }
//    std::cout << "character: " << hero.first->getCharacteristics().getCurHp() << "/"
//              << hero.first->getCharacteristics().getMaxHp() << std::endl;
//
//}


