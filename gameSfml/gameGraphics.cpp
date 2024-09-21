//
// Created by sakhd on 27.11.2023.
//
#include "gameGraphics.h"


void GameGraphics::updateGui() {


}

void GameGraphics::render() {
    window->display();
    window->clear(sf::Color(64, 64, 64));
    renderMap();
    renderEnemies();
    renderGui();
    renderPlayer();
}

void GameGraphics::renderGui() {
    auto hpPercent = static_cast<float> (static_cast<float>(game->getHero().getCharacteristics().getCurHp()) /
                                         static_cast<float>(game->getHero().getCharacteristics().getMaxHp()));

    auto manaPercent = static_cast<float> (static_cast<float>(game->getHero().getCharacteristics().getCurMana()) /
                                           static_cast<float>(game->getHero().getCharacteristics().getMaxMana()));
    auto xpPercent = static_cast<float> (static_cast<float>(game->getHero().getExp()) /
                                         static_cast<float>(EXPERIENCE_COEFFICIENT * game->getHero().getLvl()));

    playerHpBar.setSize(sf::Vector2f(120.f * hpPercent, playerHpBar.getSize().y));
    playerManaBar.setSize(sf::Vector2f(120.f * manaPercent, playerManaBar.getSize().y));
    playerXpBar.setSize(sf::Vector2f(120.f * xpPercent, playerXpBar.getSize().y));
    playerHpBar.setPosition(view.getCenter().x - 230, view.getCenter().y - 130);
    playerHpBarBack.setPosition(view.getCenter().x - 230, view.getCenter().y - 130);
    playerManaBar.setPosition(view.getCenter().x - 230, view.getCenter().y - 130 + 12);
    playerManaBarBack.setPosition(view.getCenter().x - 230, view.getCenter().y - 130 + 12);
    playerXpBar.setPosition(view.getCenter().x - 230, view.getCenter().y - 130 + 12 + 8);
    playerXpBarBack.setPosition(view.getCenter().x - 230, view.getCenter().y - 130 + 12 + 8);
    window->draw(playerHpBarBack);
    window->draw(playerHpBar);
    window->draw(playerManaBarBack);
    window->draw(playerManaBar);
    window->draw(playerXpBarBack);
    window->draw(playerXpBar);
    //Text
    currentHp.setString(std::to_string(game->getHero().getCharacteristics().getCurHp()) + "/" +
                        std::to_string(game->getHero().getCharacteristics().getMaxHp()));
    currentHp.setPosition(view.getCenter().x - 228, view.getCenter().y - 137);
    currentMana.setString(std::to_string(game->getHero().getCharacteristics().getCurMana()) + "/" +
                          std::to_string(game->getHero().getCharacteristics().getMaxMana()));
    currentMana.setPosition(view.getCenter().x - 228, view.getCenter().y - 139 + 12);
    currentEssence.setPosition(view.getCenter().x - 228, view.getCenter().y - 130 + 12 + 4);
    currentEssence.setString("Essence: " + std::to_string(game->getHero().getCountEssence()));
    window->draw(currentEssence);
    window->draw(currentHp);
    window->draw(currentMana);


    curseSprite.setColor(sf::Color::White);
    morphismSprite.setColor(sf::Color::White);
    necromancySprite.setColor(sf::Color::White);
    desiccationSprite.setColor(sf::Color::White);
    curseSprite.setPosition(view.getCenter().x - 240, view.getCenter().y + 103);
    desiccationSprite.setPosition(view.getCenter().x - 240, view.getCenter().y + 103 - 32);
    morphismSprite.setPosition(view.getCenter().x - 240, view.getCenter().y + 103 - 64);
    necromancySprite.setPosition(view.getCenter().x - 240, view.getCenter().y + 103 - 96);
    if (game->getHero().getTableSkills().getSkill(Game::allSkills[0])->getManaCost() >
        game->getHero().getCharacteristics().getCurMana() ||
        game->getHero().getTableSkills().getSkill(Game::allSkills[0])->getSkillLvl() == 0)
        curseSprite.setColor(sf::Color(25, 25, 25));
    if (
            game->getHero().getTableSkills().getSkill(Game::allSkills[1])->getSkillLvl() == 0)
        desiccationSprite.setColor(sf::Color(25, 25, 25));
    if (game->getHero().getTableSkills().getSkill(Game::allSkills[2])->getManaCost() >
        game->getHero().getCharacteristics().getCurMana() ||
        game->getHero().getTableSkills().getSkill(Game::allSkills[2])->getSkillLvl() == 0)
        morphismSprite.setColor(sf::Color(25, 25, 25));
    if (game->getHero().getTableSkills().getSkill(Game::allSkills[3])->getManaCost() >
        game->getHero().getCharacteristics().getCurMana() ||
        game->getHero().getTableSkills().getSkill(Game::allSkills[3])->getSkillLvl() == 0)
        necromancySprite.setColor(sf::Color(25, 25, 25));
    window->draw(curseSprite);
    window->draw(desiccationSprite);
    window->draw(necromancySprite);
    window->draw(morphismSprite);
    if (game->getHero().getLvlPoint() != 0) {
        for (int i = 0; i < 4; i++) {
            plusSprite.setPosition(view.getCenter().x - 240 - 4, view.getCenter().y + 103 - 32 * i + 20);
            window->draw(plusSprite);
        }
    }
    std::vector<std::string> vector = {"A", "S", "D", "F"};
    for (int i = 0; i < 4; i++) {
        text.setPosition(view.getCenter().x - 240 + 23, view.getCenter().y + 103 - 32 * i + 16);
        text.setString(
                std::to_string(game->getHero().getTableSkills().getSkill(Game::allSkills[i])->getSkillLvl()));
        window->draw(text);
        text.setPosition(view.getCenter().x - 240, view.getCenter().y + 97 - 32 * i);
        text.setString(vector[i]);
        window->draw(text);
    }
}

void GameGraphics::initGui() {

    playerHpBar.setSize(sf::Vector2f(120.f, 12.f));
    playerHpBar.setFillColor(sf::Color::Red);

    playerHpBarBack = playerHpBar;
    playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

    playerManaBar.setSize(sf::Vector2f(120.f, 8.f));
    playerManaBar.setFillColor(sf::Color::Blue);

    playerManaBarBack = playerManaBar;
    playerManaBarBack.setFillColor(sf::Color(25, 25, 25, 200));

    playerXpBar.setSize(sf::Vector2f(120.f, 3));
    playerXpBar.setFillColor(sf::Color::Green);

    playerXpBarBack = playerXpBar;
    playerXpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

    EnemyHpBar.setSize(sf::Vector2f(5.f, 2.f));
    EnemyHpBar.setFillColor(sf::Color::Red);

    EnemyHpBarBack = EnemyHpBar;
    EnemyHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

    curseTexture.loadFromFile("C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\Curse.png");
    necromancyTexture.loadFromFile("C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\Necromance.png");
    morphismTexture.loadFromFile("C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\Morphism.png");
    desiccationTexture.loadFromFile("C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\descition.png");

    curseSprite.setTexture(curseTexture);
    necromancySprite.setTexture(necromancyTexture);
    morphismSprite.setTexture(morphismTexture);
    desiccationSprite.setTexture(desiccationTexture);

    plusTexture.loadFromFile("C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\plus.png");
    plusSprite.setTexture(plusTexture);
    plusSprite.setColor(sf::Color(255, 211, 0, 100));

}

void
GameGraphics::getplayercoordinateforview(float x, float y) { //функция для считывания координат игрока
    float tempX = x;
    float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края

    if (x < 200) tempX = 200;//убираем из вида левую сторону
    if (y < 100) tempY = 100;//верхнюю сторону
    if (y > 700) tempY = 700;//нижнюю сторону
    view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты.
}

void GameGraphics::initView() {
    view.reset(sf::FloatRect(0, 0, 480, 270));
}

void GameGraphics::renderMap() {

    for (int i = 0; i < game->getAllMap()[game->getCurLvl()].getHeight(); i++)
        for (int j = 0; j < game->getAllMap()[game->getCurLvl()].getWigth(); j++) {
            if (game->getAllMap()[game->getCurLvl()].getMapLevel()[i][j] == Ceil::floor)
                s_map.setTextureRect(
                        sf::IntRect(64, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
            if (game->getAllMap()[game->getCurLvl()].getMapLevel()[i][j] == Ceil::wall)
                s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
            if (game->getAllMap()[game->getCurLvl()].getMapLevel()[i][j] == Ceil::lava)
                s_map.setTextureRect(sf::IntRect(96, 0, 32, 32));
            if (game->getAllMap()[game->getCurLvl()].getMapLevel()[i][j] == Ceil::essence)
                s_map.setTextureRect(sf::IntRect(128, 0, 32, 32));
            if (game->getAllMap()[game->getCurLvl()].getMapLevel()[i][j] == Ceil::closeDoor)
                s_map.setTextureRect(sf::IntRect(160, 0, 32, 32));
            if (game->getAllMap()[game->getCurLvl()].getMapLevel()[i][j] == Ceil::openDoor)
                s_map.setTextureRect(sf::IntRect(192, 0, 32, 32));
            if (game->getAllMap()[game->getCurLvl()].getMapLevel()[i][j] == Ceil::ladder) {
                if (game->getCurLvl() % 2 != 0)
                    s_map.setTextureRect(sf::IntRect(224, 0, 32, 32));
                else s_map.setTextureRect(sf::IntRect(256, 0, 32, 32));
            }
            s_map.setPosition(j * 32, i * 32);

            window->draw(s_map);//рисуем квадратики на экран
        }
}

void GameGraphics::initSmap() {
    map_image.loadFromFile("C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\map.png");
    map.loadFromImage(map_image);
    s_map.setTexture(map);
}

void GameGraphics::initEnemies() {
    golemTexture.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\Golem\\Character_sheet.png");
    golemSprite.setTexture(golemTexture);

    undeadTexture.loadFromFile("C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\Undead.png");
    undeadSprite.setTexture(undeadTexture);

    livingEnemyTexture.loadFromFile("C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\Knight.png");
    livingEnemySprite.setTexture(livingEnemyTexture);

    undeadSummonerTexture.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\GrandmasterWarlockIdle.png");
    undeadSummonerSprite.setTexture(undeadSummonerTexture);

    livingSummonerTexture.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\ElfArchmageIdleSide.png");
    livingSummonerSprite.setTexture(livingSummonerTexture);
}

void GameGraphics::renderEnemies() {
    for (auto enemy: game->getAllMap()[game->getCurLvl()].getListEnemies()) {
        auto percent = static_cast<float> (static_cast<float>(enemy.first->getCurHp()) /
                                           static_cast<float>( enemy.first->getMaxHp()));
        if (static_cast<float> (enemy.first->getMaxHp()) * percent >= 50) {
            EnemyHpBar.setSize(sf::Vector2f(50, EnemyHpBar.getSize().y));
        } else {
            EnemyHpBar.setSize(
                    sf::Vector2f(static_cast<float> (enemy.first->getMaxHp()) * percent, EnemyHpBar.getSize().y));
        }
        EnemyHpBar.setPosition(static_cast<float> (enemy.first->getCoords().second) * 32,
                               static_cast<float> (enemy.first->getCoords().first) * 32);
        EnemyHpBarBack.setPosition(static_cast<float> (enemy.first->getCoords().second) * 32,
                                   static_cast<float> (enemy.first->getCoords().first) * 32);
        window->draw(EnemyHpBarBack);
        window->draw(EnemyHpBar);
        if (enemy.first->getName() == Game::allTypesEnemies[3]) {
            if (enemy.first->getSideLooking() == SideLooking::right) {
                undeadSummonerSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
            }
            if (enemy.first->getSideLooking() == SideLooking::left) {
                undeadSummonerSprite.setTextureRect(sf::IntRect(32, 0, -32, 32));
            }
            undeadSummonerSprite.setPosition(static_cast<float > (enemy.first->getCoords().second * 32),
                                             static_cast<float > (enemy.first->getCoords().first * 32 ));
            window->draw(undeadSummonerSprite);
        } else if (enemy.first->getName() == Game::allTypesEnemies[1]) {
            if (enemy.first->getSideLooking() == SideLooking::right) {
                livingSummonerSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
            }
            if (enemy.first->getSideLooking() == SideLooking::left) {
                livingSummonerSprite.setTextureRect(sf::IntRect(32, 0, -32, 32));
            }
            if (enemy.first->getStatus() == Status::dead && enemy.first->getSideLooking() == SideLooking::right) {
                livingSummonerSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
            }
            if (enemy.first->getStatus() == Status::dead && enemy.first->getSideLooking() == SideLooking::left) {
                livingSummonerSprite.setTextureRect(sf::IntRect(32 + 32, 0, -32, 32));
            }
            livingSummonerSprite.setPosition(static_cast<float > (enemy.first->getCoords().second * 32),
                                             static_cast<float > (enemy.first->getCoords().first * 32 ));
            window->draw(livingSummonerSprite);

        } else if (enemy.first->getFaction() == Faction::golem) {
            if (enemy.first->getSideLooking() == SideLooking::right) {
                golemSprite.setTextureRect(sf::IntRect(18, 18, 64, 64));
            }
            if (enemy.first->getSideLooking() == SideLooking::left) {
                golemSprite.setTextureRect(sf::IntRect(18 + 64, 18, -64, 64));
            }
            golemSprite.setColor(sf::Color::White);
            golemSprite.setPosition(static_cast<float > (enemy.first->getCoords().second * 32),
                                    static_cast<float > (enemy.first->getCoords().first * 32 ));
            if (dynamic_cast<Golem *>(enemy.first)->getCeil() == Ceil::essence)
                golemSprite.setColor(sf::Color(238, 130, 238));
            else if (dynamic_cast<Golem *>(enemy.first)->getCeil() == Ceil::lava)
                golemSprite.setColor(sf::Color(255, 64, 25));
            window->draw(golemSprite);
        } else if (enemy.first->getFaction() == Faction::undead || enemy.first->getName() == Game::allTypesEnemies[2]) {
            if (enemy.first->getSideLooking() == SideLooking::right) {
                undeadSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
            }
            if (enemy.first->getSideLooking() == SideLooking::left) {
                undeadSprite.setTextureRect(sf::IntRect(32, 0, -32, 32));
            }
            undeadSprite.setPosition(static_cast<float > (enemy.first->getCoords().second * 32),
                                     static_cast<float > (enemy.first->getCoords().first * 32 ));
            window->draw(undeadSprite);
        } else if (enemy.first->getFaction() == Faction::livingEnemy) {
            if (enemy.first->getSideLooking() == SideLooking::right) {
                livingEnemySprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
            }
            if (enemy.first->getSideLooking() == SideLooking::left) {
                livingEnemySprite.setTextureRect(sf::IntRect(32, 0, -32, 32));
            }
            if (enemy.first->getStatus() == Status::dead && enemy.first->getSideLooking() == SideLooking::right) {
                livingEnemySprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
            }
            if (enemy.first->getStatus() == Status::dead && enemy.first->getSideLooking() == SideLooking::left) {
                livingEnemySprite.setTextureRect(sf::IntRect(32 + 32, 0, -32, 32));
            }
            livingEnemySprite.setPosition(static_cast<float > (enemy.first->getCoords().second * 32),
                                          static_cast<float > (enemy.first->getCoords().first * 32 ));
            window->draw(livingEnemySprite);
        }
    }

}


void GameGraphics::start() {
    menu();
    initSmap();
    initGui();
    initPlayer();
    initView();
    initText();
    initEnemies();
    game->getHero().upLVL();
    game->getHero().upLVL();
    game->getHero().upLVL();
    game->getHero().upLVL();
    game->getHero().increaseExp(50);
    game->getHero().setCountEssence(1000);
//    game->getHero().getOpenEnemies().emplace_back("livingEnemy");
//    game->getHero().getOpenEnemies().emplace_back("livingSummoner");
    bool dead = false;
    bool win = false;
    while (window->isOpen()) {
        sf::Event event;
        time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
        clock.restart();
        time /= 10000;
        getplayercoordinateforview(static_cast<float> (game->getHero().getCoords().second * 32),
                                   static_cast<float> (game->getHero().getCoords().first * 32));
        window->setView(view);
        render();
        deadText.setPosition(view.getCenter().x - 130, view.getCenter().y - 50);
        winText.setPosition(view.getCenter().x - 130, view.getCenter().y - 50);
        if (game->getCurLvl() == game->getMaxLvl()) win = true;
        if (dead && !win) window->draw(deadText);
        if (win) window->draw(winText);
        currentFrame += time * 0.05;
        attackFrame += time * 0.05;
        while (window->pollEvent(event)) // poll event
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (game->getHero().getCharacteristics().getCurHp() > 0 && !win) {
                if (event.type == sf::Event::KeyReleased)
                    tick(event);
                if (event.type == sf::Event::KeyPressed)
                    tick(event);
                if (event.type == sf::Event::MouseButtonPressed)
                    tick(event);
                if (event.type == sf::Event::MouseButtonReleased)
                    tick(event);
            } else {
                dead = true;
            }
            break;
        }
        if (currentFrame > 3) {
            currentFrame = 0;
            game->getAllMap()[game->getCurLvl()].allDoSomething();
        }
        if (attackFrame > 2 && !win) {
            canAttack = true;
            attackFrame = 0;
        }

    }
}

void GameGraphics::renderPlayer() {
    heroRightSprite.setPosition(static_cast<float>(game->getHero().getCoords().second * 32),
                                static_cast<float>(game->getHero().getCoords().first * 32));
    window->draw(heroRightSprite);
}

void GameGraphics::initPlayer() {

    heroRight.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Right\\Png\\NecromancerRightRun.png");

    heroRightSprite.setTexture(heroRight);
    heroRightSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

    heroUp.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Up\\Png\\NecromancerUpRun.png");

    heroDown.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Down\\Png\\NecromancerDownRun.png");

    heroLeft.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Left\\Png\\NecromancerLeftRun.png");

    takeEssence.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Down\\Png\\NecromancerDownLand.png");


    attackTexture.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Down\\Png\\NecromancerDownAttack01.png");

    heroNecro.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Down\\Png\\NecromancerDownAttack03.png");

    heroCurseDown.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Down\\Png\\NecromancerDownAttack02.png");
    heroCurseLeft.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Left\\Png\\NecromancerLeftAttack02.png");
    heroCurseRight.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Right\\Png\\NecromancerRightAttack02.png");
    heroCurseUp.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Up\\Png\\NecromancerUpAttack02.png");

    heroMorphDown.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Down\\Png\\NecromancerDownAttack03.png");
    heroMorphLeft.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Left\\Png\\NecromancerLeftAttack03.png");
    heroMorphRight.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Right\\Png\\NecromancerRightAttack03.png");
    heroMorphUp.loadFromFile(
            "C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\hero\\Up\\Png\\NecromancerUpAttack03.png");

}

int GameGraphics::tick(sf::Event event) {
    if (event.key.code == sf::Keyboard::Left && event.type == sf::Event::KeyReleased) {
        heroRightSprite.setTexture(heroLeft);
        game->makeTick(Game::option[1]);
        heroRightSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
    } else if (event.key.code == sf::Keyboard::Right && event.type == sf::Event::KeyReleased) {
        game->makeTick(Game::option[0]);
        heroRightSprite.setTexture(heroRight);
        heroRightSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
    } else if (event.key.code == sf::Keyboard::Up && event.type == sf::Event::KeyReleased) {
        game->makeTick(Game::option[2]);
        heroRightSprite.setTexture(heroUp);
        heroRightSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
    } else if (event.key.code == sf::Keyboard::Down && event.type == sf::Event::KeyReleased) {
        game->makeTick(Game::option[3]);
        heroRightSprite.setTexture(heroDown);
        heroRightSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        game->makeTick(Game::option[6]);
        game->getHero().openEnemy(game->getAllMap()[game->getCurLvl()]);
        heroRightSprite.setTexture(takeEssence);
        heroRightSprite.setTextureRect(sf::IntRect(48, 0, 48, 48));
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && canAttack) {
        game->makeTick(Game::option[11]);
        heroRightSprite.setTexture(attackTexture);
        heroRightSprite.setTextureRect(sf::IntRect(6 * 48, 0, 48, 48));
        canAttack = false;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
        game->makeTick(Game::option[4]);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        game->makeTick(Game::option[5]);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
        game->makeTick(Game::option[8]);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        game->makeTick(Game::option[7]);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        int mas[3] = {};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            mas[0] = 11;
            mas[1] = 0;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            mas[0] = 11;
            mas[1] = 1;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
            mas[0] = 11;
            mas[1] = 2;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            mas[0] = 11;
            mas[1] = 3;
        }
        game->makeTick(mas);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        int mas[2] = {10, 0};
        switch (game->getHero().getSideLooking()) {
            case Move::right: {
                heroRightSprite.setTexture(heroCurseRight);
                heroRightSprite.setTextureRect(sf::IntRect(48 * 5, 0, 48, 48));
                break;
            }
            case Move::left: {
                heroRightSprite.setTexture(heroCurseLeft);
                heroRightSprite.setTextureRect(sf::IntRect(48 * 5, 0, 48, 48));
                break;
            }
            case Move::up: {
                heroRightSprite.setTexture(heroCurseUp);
                heroRightSprite.setTextureRect(sf::IntRect(48 * 5, 0, 48, 48));
                break;
            }
            case Move::down: {
                heroRightSprite.setTexture(heroCurseDown);
                heroRightSprite.setTextureRect(sf::IntRect(48 * 5, 0, 48, 48));
                break;
            }
        }
        game->makeTick(mas);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        int mas[2] = {10, 1};
        game->makeTick(mas);
        heroRightSprite.setTexture(takeEssence);
        heroRightSprite.setTextureRect(sf::IntRect(48, 0, 48, 48));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
        int mas[2] = {10, 3};
        game->makeTick(mas);
        heroRightSprite.setTexture(heroNecro);
        heroRightSprite.setTextureRect(sf::IntRect(48 * 8, 0, 48, 48));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
        int mas[3] = {10, 2};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) mas[2] = 2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && sf::Keyboard::isKeyPressed(sf::Keyboard::X)) mas[2] = 3;
        switch (game->getHero().getSideLooking()) {
            case Move::right: {
                heroRightSprite.setTexture(heroMorphRight);
                heroRightSprite.setTextureRect(sf::IntRect(48 * 5, 0, 48, 48));
                break;
            }
            case Move::left: {
                heroRightSprite.setTexture(heroMorphLeft);
                heroRightSprite.setTextureRect(sf::IntRect(48 * 5, 0, 48, 48));
                break;
            }
            case Move::up: {
                heroRightSprite.setTexture(heroMorphUp);
                heroRightSprite.setTextureRect(sf::IntRect(48 * 5, 0, 48, 48));
                break;
            }
            case Move::down: {
                heroRightSprite.setTexture(heroMorphDown);
                heroRightSprite.setTextureRect(sf::IntRect(48 * 5, 0, 48, 48));
                break;
            }
        }
        game->makeTick(mas);
    } else {
        heroRightSprite.setTexture(heroDown);
        heroRightSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
    }
    return 1;
}

void GameGraphics::initText() {
    font.loadFromFile("C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\Minipower.ttf");
    currentHp.setOutlineThickness(1);
    currentHp.setOutlineColor(sf::Color::Black);
    currentHp.setFont(font);
    currentHp.setCharacterSize(15);
    currentHp.setString(std::to_string(game->getHero().getCharacteristics().getCurHp()));
    currentMana.setFont(font);
    currentMana.setCharacterSize(15);
    currentMana.setString(std::to_string(game->getHero().getCharacteristics().getCurMana()));
    currentMana.setOutlineThickness(1);
    currentMana.setOutlineColor(sf::Color::Black);
    currentEssence.setFont(font);
    currentEssence.setCharacterSize(15);
    currentEssence.setOutlineThickness(1);
    currentEssence.setOutlineColor(sf::Color::Black);
    currentEssence.setFillColor(sf::Color::Magenta);
    currentEssence.setString("Essence " + std::to_string(game->getHero().getCountEssence()));
    currentLvl.setFont(font);
    currentLvl.setCharacterSize(15);
    currentLvl.setString(std::to_string(game->getHero().getCharacteristics().getCurMana()));

    text.setFont(menuFont);
    text.setCharacterSize(15);;
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);

    deadText.setFont(menuFont);
    deadText.setCharacterSize(50);;
    deadText.setOutlineColor(sf::Color::Black);
    deadText.setOutlineThickness(10);
    deadText.setFillColor(sf::Color::Red);
    deadText.setString("You`re dead!");

    winText.setFont(menuFont);
    winText.setCharacterSize(50);;
    winText.setOutlineColor(sf::Color::Black);
    winText.setOutlineThickness(10);
    winText.setFillColor(sf::Color::Yellow);
    winText.setString("You`re win!");
}

void GameGraphics::menu() {
    backGroundTexture.loadFromFile("C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\menuBackGround.jpg");
    backGroundSprite.setTexture(backGroundTexture);
    menuFont.loadFromFile("C:\\Users\\sakhd\\CLionProjects\\gameLab3\\gameSfml\\images\\ThaleahFat.ttf");
    menuStart.setFont(menuFont);
    menuExit.setFont(menuFont);
    menuStart.setOutlineThickness(10);
    menuStart.setOutlineColor(sf::Color::Black);
    menuStart.setCharacterSize(150);
    menuStart.setString("Start game");
    menuStart.setPosition(window->getSize().x / 3, window->getSize().y / 4);
    menuExit.setOutlineThickness(10);
    menuExit.setOutlineColor(sf::Color::Black);
    menuExit.setCharacterSize(150);
    menuExit.setString("Exit");
    menuExit.setPosition(window->getSize().x / 2.2, window->getSize().y / 4 + 150);
    bool isMenu = true;
    int menuNum = 0;

    while (window->isOpen() && isMenu) {
        window->clear(sf::Color(129, 181, 221));
        menuStart.setFillColor(sf::Color::White);
        menuExit.setFillColor(sf::Color::White);
        sf::Event event;
        if (sf::IntRect(window->getSize().x / 3, window->getSize().y / 4, 1500, 150).contains(
                sf::Mouse::getPosition(*window))) {
            menuStart.setFillColor(sf::Color::Magenta);
            menuNum = 1;
        }
        if (sf::IntRect(window->getSize().x / 2.2, window->getSize().y / 4 + 150, 750, 150).contains(
                sf::Mouse::getPosition(*window))) {
            menuExit.setFillColor(sf::Color::Magenta);
            menuNum = 2;
        }
        while (window->pollEvent(event)) // poll event
        {
            if (event.type == sf::Event::Closed) {
                window->close();
            }


        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню
            if (menuNum == 2) window->close();
        }
        window->draw(backGroundSprite);
        window->draw(menuStart);
        window->draw(menuExit);
        window->display();
    }

}

