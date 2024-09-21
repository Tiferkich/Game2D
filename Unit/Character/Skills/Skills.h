//
// Created by sakhd on 18.11.2023.
//

#ifndef GAMELAB3_SKILLS_H
#define GAMELAB3_SKILLS_H

class Dungeon;


///Абстрактный класс от которого наследуются все скиллы
class Skill {
protected:
    int skillLvl;///< Уровень скилла
    int manaCost;///< Мана кост скилла
public:
    /// Конструктор
    /// \param manaCost - Мана кост скилла
    explicit Skill(int manaCost) : skillLvl(0), manaCost(manaCost) {};
    /// Чисто виртуальный метод
    /// \param dungeon - уровень
    /// \param mas - массив опций
    /// \return 0 - успех
    virtual int useSkill(Dungeon &dungeon, int mas[]) = 0;

    /// Getter
    /// \return - Текущий уровень скилла
    int getSkillLvl() const {
        return skillLvl;
    }

    /// Setter
    /// \param lvl - новый уровень скилла
    Skill &setSkillLvl(int lvl) {
        skillLvl = lvl;
        return *this;
    }

    /// Прокачать скилл
    /// \return уровень скилла
    int upgradeLvl() {
        return ++skillLvl;
    }

    int getManaCost() const {
        return manaCost;
    }

};


#endif //GAMELAB3_SKILLS_H
