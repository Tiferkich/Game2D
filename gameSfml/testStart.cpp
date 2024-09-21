//
// Created by sakhd on 27.11.2023.
//
#include "../Unit/Character/Character.h"
#include "gameGraphics.h"
#include "../Unit/Enemy/Summoner/UndeadSummoner.h"
#include "../Unit/Enemy/Summoner/LivingSummoner.h"
#include "maps/map.1.h"
#include "../Unit/Character/Skills/Curse/Curse.h"
#include "../Unit/Character/Skills/Desiccation/Desiccation.h"
#include "../Unit/Character/Skills/Necromancy/Necromancy.h"
#include "../Unit/Character/Skills/Morphism/Morphism.h"
#include "maps/map.2.h"
#include "maps/map.3.h"

int main() {
    Game game;
    std::list<std::pair<Enemy *, Ceil *>> listEnemies;
    Matrix<Ceil> matrix(25, 40);
    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++) {
            if (TileMap[i][j] == ' ')
                matrix[i][j] = Ceil::floor;
            else if ((TileMap[i][j] == '0'))
                matrix[i][j] = Ceil::wall;
            else if ((TileMap[i][j] == 'l'))
                matrix[i][j] = Ceil::lava;
            else if ((TileMap[i][j] == 'e'))
                matrix[i][j] = Ceil::essence;
            else if ((TileMap[i][j] == 'O'))
                matrix[i][j] = Ceil::openDoor;
            else if ((TileMap[i][j] == 'C'))
                matrix[i][j] = Ceil::closeDoor;
            else if ((TileMap[i][j] == 'L'))
                matrix[i][j] = Ceil::ladder;
        }
    Matrix<Ceil> matrix2(25, 40);
    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++) {
            if (TileMap2[i][j] == ' ')
                matrix2[i][j] = Ceil::floor;
            else if ((TileMap2[i][j] == '0'))
                matrix2[i][j] = Ceil::wall;
            else if ((TileMap2[i][j] == 'l'))
                matrix2[i][j] = Ceil::lava;
            else if ((TileMap2[i][j] == 'e'))
                matrix2[i][j] = Ceil::essence;
            else if ((TileMap2[i][j] == 'O'))
                matrix2[i][j] = Ceil::openDoor;
            else if ((TileMap2[i][j] == 'C'))
                matrix2[i][j] = Ceil::closeDoor;
            else if ((TileMap2[i][j] == 'L'))
                matrix2[i][j] = Ceil::ladder;
        }
    Matrix<Ceil> matrix3(25, 40);
    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++) {
            if (TileMap3[i][j] == ' ')
                matrix3[i][j] = Ceil::floor;
            else if ((TileMap3[i][j] == '0'))
                matrix3[i][j] = Ceil::wall;
            else if ((TileMap3[i][j] == 'l'))
                matrix3[i][j] = Ceil::lava;
            else if ((TileMap3[i][j] == 'e'))
                matrix3[i][j] = Ceil::essence;
            else if ((TileMap3[i][j] == 'O'))
                matrix3[i][j] = Ceil::openDoor;
            else if ((TileMap3[i][j] == 'C'))
                matrix3[i][j] = Ceil::closeDoor;
            else if ((TileMap3[i][j] == 'L'))
                matrix3[i][j] = Ceil::ladder;
        }
    Dungeon dungeon1(listEnemies, matrix, matrix.cols(), matrix.rows(),
                     {&game.getHero(),
                      &matrix[game.getHero().getCoords().second][game.getHero().getCoords().first]});

    Dungeon dungeon2(listEnemies, matrix2, matrix2.cols(), matrix2.rows(),
                     {&game.getHero(),
                      &matrix2[game.getHero().getCoords().second][game.getHero().getCoords().first]});
    Dungeon dungeon3(listEnemies, matrix3, matrix3.cols(), matrix3.rows(),
                     {&game.getHero(),
                      &matrix3[game.getHero().getCoords().second][game.getHero().getCoords().first]});
    std::vector<Dungeon> allmap;
    allmap.emplace_back(dungeon1);
    allmap.emplace_back(dungeon2);
    allmap.emplace_back(dungeon3);
    game.setAllMap(allmap);
    LivingEnemy knight(10, {6, 10}, {15, 20}, 50, 50);
    LivingEnemy knight1(10, {6, 10}, {16, 16}, 50, 50);
    LivingEnemy knight2(10, {6, 10}, {17, 14}, 50, 50);
    LivingEnemy knight3(10, {6, 10}, {10, 10}, 50, 50);
    LivingEnemy knight4(10, {6, 10}, {10, 11}, 50, 50);
    LivingEnemy knight5(10, {6, 10}, {15, 18}, 50, 50);
    Undead undead(10, {0, 5}, {1, 9}, 50, 50);
    Undead undead1(10, {0, 5}, {2, 9}, 50, 50);
    Undead undead2(10, {0, 5}, {3, 9}, 50, 50);
    Undead undead3(10, {0, 5}, {2, 9}, 50, 50);
    Undead undead4(10, {0, 5}, {3, 9}, 50, 50);
    Undead undead5(10, {0, 5}, {4, 9}, 50, 50);
    game.getAllMap()[0] += {&undead,
                            &game.getAllMap()[0].getMapLevel()[undead.getCoords().second][undead.getCoords().first]};
    game.getAllMap()[0] += {&undead1,
                            &game.getAllMap()[0].getMapLevel()[undead1.getCoords().second][undead1.getCoords().first]};
    game.getAllMap()[0] += {&undead2,
                            &game.getAllMap()[0].getMapLevel()[undead2.getCoords().second][undead2.getCoords().first]};
    game.getAllMap()[0] += {&undead3,
                            &game.getAllMap()[0].getMapLevel()[undead3.getCoords().second][undead3.getCoords().first]};
    game.getAllMap()[0] += {&undead4,
                            &game.getAllMap()[0].getMapLevel()[undead4.getCoords().second][undead4.getCoords().first]};
    game.getAllMap()[0] += {&undead5,
                            &game.getAllMap()[0].getMapLevel()[undead5.getCoords().second][undead5.getCoords().first]};
    game.getAllMap()[0] += {&knight,
                            &game.getAllMap()[0].getMapLevel()[knight.getCoords().second][knight.getCoords().first]};
    game.getAllMap()[0] += {&knight1,
                            &game.getAllMap()[0].getMapLevel()[knight1.getCoords().second][knight1.getCoords().first]};
    game.getAllMap()[0] += {&knight2,
                            &game.getAllMap()[0].getMapLevel()[knight2.getCoords().second][knight2.getCoords().first]};
    game.getAllMap()[0] += {&knight3,
                            &game.getAllMap()[0].getMapLevel()[knight3.getCoords().second][knight3.getCoords().first]};
    game.getAllMap()[0] += {&knight4,
                            &game.getAllMap()[0].getMapLevel()[knight4.getCoords().second][knight4.getCoords().first]};
    game.getAllMap()[0] += {&knight5,
                            &game.getAllMap()[0].getMapLevel()[knight5.getCoords().second][knight5.getCoords().first]};


    Golem golem(10, {10, 15}, {15, 3}, 200, 0, Ceil::essence);
    Golem golem1(10, {10, 15}, {15, 4}, 200, 0, Ceil::lava);
    Golem golem2(10, {10, 15}, {15, 5}, 200, 0, Ceil::floor);
    LivingSummoner livingSummoner(10, {2, 10}, {20, 20}, 100);
    UndeadSummoner undeadSummoner(10, {20, 10}, {2, 2}, 100, 100);
    Golem golem3(10, {10, 15}, {15, 6}, 200, 0, Ceil::essence);
    Golem golem4(10, {10, 15}, {15, 7}, 200, 0, Ceil::lava);
    Golem golem5(10, {10, 15}, {15, 8}, 200, 0, Ceil::floor);
    LivingSummoner livingSummoner1(10, {5, 10}, {20, 20}, 150);
    UndeadSummoner undeadSummoner1(10, {20, 10}, {2, 2}, 150, 150);
    game.getAllMap()[1] += {&livingSummoner,
                            &game.getAllMap()[1].getMapLevel()[livingSummoner.getCoords().second][livingSummoner.getCoords().first]};
    game.getAllMap()[1] += {&undeadSummoner,
                            &game.getAllMap()[1].getMapLevel()[undeadSummoner.getCoords().second][undeadSummoner.getCoords().first]};
    game.getAllMap()[1] += {&livingSummoner1,
                            &game.getAllMap()[1].getMapLevel()[livingSummoner1.getCoords().second][livingSummoner1.getCoords().first]};
    game.getAllMap()[1] += {&undeadSummoner1,
                            &game.getAllMap()[1].getMapLevel()[undeadSummoner1.getCoords().second][undeadSummoner1.getCoords().first]};
//    game.getAllMap()[1] += {&golem,
//                            &game.getAllMap()[1].getMapLevel()[golem.getCoords().second][golem.getCoords().first]};
//    game.getAllMap()[1] += {&golem1,
//                            &game.getAllMap()[1].getMapLevel()[golem1.getCoords().second][golem1.getCoords().first]};
//    game.getAllMap()[1] += {&golem2,
//                            &game.getAllMap()[1].getMapLevel()[golem2.getCoords().second][golem2.getCoords().first]};
    game.getAllMap()[1] += {&golem3,
                            &game.getAllMap()[1].getMapLevel()[golem3.getCoords().second][golem3.getCoords().first]};
    game.getAllMap()[1] += {&golem4,
                            &game.getAllMap()[1].getMapLevel()[golem4.getCoords().second][golem4.getCoords().first]};
    game.getAllMap()[1] += {&golem5,
                            &game.getAllMap()[1].getMapLevel()[golem5.getCoords().second][golem5.getCoords().first]};

    Curse curse(25);
    Desiccation desiccation;
    Necromancy necromancy(25);
    Morphism morphism(25);

    game.getHero().getTableSkills().addSkill(&curse, "Curse");
    game.getHero().getTableSkills().addSkill(&desiccation, "Desiccation");
    game.getHero().getTableSkills().addSkill(&necromancy, "Necromancy");
    game.getHero().getTableSkills().addSkill(&morphism, "Morphism");
    game.getHero().getTableSkills().upgradeSkill("Morphism");

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Necromancer 1");
    GameGraphics gameGraphics(&game, &window);
    gameGraphics.start();
}
