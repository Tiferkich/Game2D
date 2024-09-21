//
// Created by sakhd on 18.11.2023.
//

#ifndef GAMELAB3_TABLESKILLS_H
#define GAMELAB3_TABLESKILLS_H

#include <iostream>
#include <map>

#include "Skills/Skills.h"


///Класс - таблица скиллов героя
class TableSkills {
private:
    std::map<std::string, Skill *> skills;///< Таблица скиллов

public:
    /// Метод улучшения выбранного скила
    /// \param name - Название скила
    /// \return 0 - если есть такой скил; -1 если его нет
    int upgradeSkill(const std::string &name) {
        auto it = skills.find(name);
        if (it == skills.end()) return -1;
        skills[name]->upgradeLvl();
        return 0;
    }

    /// \return - Кол-во доступных скилов
    int countSkills() const {
        return skills.size();
    }

    /// Метод добавления нового скила
    /// \param newSkill - Указатель на новый скил
    /// \param name - Название скила
    /// \return 0 - если есть такой скил; -1 если его нет

    int addSkill(Skill *newSkill, const std::string &name) {
        skills.insert({name, newSkill});
        return 0;
    }
    ///  Setter
    /// \param newSkill - новый скилл
    /// \param name  - Название скилла
    /// \return возвращает ссылку самого себя для цепного обращения
    TableSkills &setSkill(Skill *newSkill, const std::string &name) {
        auto it = skills.find(name);
        if (it == skills.end()) return *this;
        skills[name] = newSkill;
        return *this;
    }

    /// Getter
    /// \param name - Название скилла
    /// \throw std::invalid_argument - Если нет такого скила
    /// \return возвращает его
    Skill *getSkill(const std::string &name) {
        auto it = skills.find(name);
        if (it == skills.end()) throw (std::invalid_argument("No skill"));
        return skills[name];
    }


};


#endif //GAMELAB3_TABLESKILLS_H
