//
// Created by gotham on 10.05.2025.
//

#ifndef DIFFICULTYMANAGER_H
#define DIFFICULTYMANAGER_H
#pragma once
#include "Difficulty.h"
#include <string>


class DifficultyManager {
    public:
        DifficultyManager(Difficulty& difficultyEnum, float& spawnTime, float& speed, float& spawnRate);
        void changeDifficulty();
        void nextDifficulty();
        Difficulty& getDifficulty();
        float getDifficultyMultiplier();
    private:
        Difficulty& difficultyEnum;
        float& spawnTime;
        float& speed;
        float& spawnRate;
        float  difficultyMultiplier;
};



#endif //DIFFICULTYMANAGER_H
