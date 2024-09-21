//
// Created by sakhd on 25.10.2023.
//

#ifndef GAMELAB3_CEIL_H
#define GAMELAB3_CEIL_H




/// Набор возможных состояний клетки
enum class Ceil {
    wall, ///< Стена, через нее нельзя ходить
    floor,
    lava,
    openDoor,
    closeDoor,
    essence,///< Нужна для сбора и открытия персонажей
    ladder ///< Лестница нужна для передвижения по этажам
};


#endif //GAMELAB3_CEIL_H
