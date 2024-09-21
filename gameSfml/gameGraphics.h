//
// Created by sakhd on 27.11.2023.
//

#ifndef GAMELAB3_GAMEGRAPHICS_H
#define GAMELAB3_GAMEGRAPHICS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../Game/Game.h"
#include <chrono>
#include <thread>


class GameGraphics {
    Game *game;
    sf::RenderWindow *window;
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;
    sf::RectangleShape playerManaBar;
    sf::RectangleShape playerManaBarBack;
    sf::RectangleShape playerXpBar;
    sf::RectangleShape playerXpBarBack;
    sf::RectangleShape EnemyHpBar;
    sf::RectangleShape EnemyHpBarBack;

    sf::Image map_image;
    sf::View view;

    sf::Sprite s_map;
    sf::Sprite golemSprite;
    sf::Sprite heroRightSprite;
    sf::Sprite undeadSprite;
    sf::Sprite livingEnemySprite;
    sf::Sprite livingSummonerSprite;
    sf::Sprite undeadSummonerSprite;
    sf::Sprite backGroundSprite;
    sf::Sprite necromancySprite;
    sf::Sprite morphismSprite;
    sf::Sprite desiccationSprite;
    sf::Sprite curseSprite;
    sf::Sprite plusSprite;

    sf::Texture heroRight;
    sf::Texture heroUp;
    sf::Texture heroDown;
    sf::Texture heroLeft;
    sf::Texture takeEssence;
    sf::Texture attackTexture;
    sf::Texture golemTexture;
    sf::Texture map;
    sf::Texture undeadTexture;
    sf::Texture livingEnemyTexture;
    sf::Texture livingSummonerTexture;
    sf::Texture undeadSummonerTexture;
    sf::Texture backGroundTexture;
    sf::Texture necromancyTexture;
    sf::Texture morphismTexture;
    sf::Texture desiccationTexture;
    sf::Texture curseTexture;
    sf::Texture plusTexture;
    sf::Texture heroNecro;
    sf::Texture heroCurseRight;
    sf::Texture heroCurseLeft;
    sf::Texture heroCurseUp;
    sf::Texture heroCurseDown;
    sf::Texture heroMorphRight;
    sf::Texture heroMorphLeft;
    sf::Texture heroMorphUp;
    sf::Texture heroMorphDown;


    sf::Clock clock;
    sf::Font font;
    sf::Font menuFont;
    sf::Text currentHp;
    sf::Text currentMana;
    sf::Text currentEssence;
    sf::Text currentLvl;
    sf::Text text;
    sf::Text deadText;
    sf::Text winText;

    sf::Text menuStart;
    sf::Text menuExit;


    bool canAttack = true;
    float attackFrame = 0;
    float time = 0;
    float currentFrame = 0;
public:
    explicit GameGraphics(Game *game = nullptr, sf::RenderWindow *window = nullptr) : game(game), window(window) {};

    void start();

    void initText();


    void menu();

    int tick(sf::Event event);

    void initSmap();

    void renderMap();

    void initPlayer();

    void renderPlayer();

    void render();

    void updateGui();

    void renderGui();

    void initGui();

    void initView();

    void getplayercoordinateforview(float x, float y);

    void initEnemies();

    void renderEnemies();
};

#endif //GAMELAB3_GAMEGRAPHICS_H
