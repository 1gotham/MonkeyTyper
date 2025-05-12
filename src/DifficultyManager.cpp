//
// Created by gotham on 10.05.2025.
//

#include "DifficultyManager.h"

#include <iostream>
#include <ostream>

DifficultyManager::DifficultyManager(Difficulty& difficultyEnum, float& spawnTime, float& speed, float& spawnRate) : difficultyEnum(difficultyEnum), spawnTime(spawnTime), speed(speed), spawnRate(spawnRate) {
    difficultyMultiplier = 1;
}

void DifficultyManager::changeDifficulty() {
    switch (difficultyEnum) {
        case Difficulty::Easy: {
            spawnTime = 2.f;
            speed = 0.2f;
            spawnRate = 1.f;
            difficultyMultiplier = 0.7f;
            break;
        }
        case Difficulty::Medium: {
            spawnTime = 1.7f;
            speed = 0.3f;
            spawnRate = 2.f;
            difficultyMultiplier = 1.f;
            break;
        }
        case Difficulty::Hard: {
            spawnTime = 1.2f;
            speed = 0.4f;
            spawnRate = 3.0f;
            difficultyMultiplier = 1.5f;
            break;
        }
        case Difficulty::Extreme: {
            spawnTime = 0.9f;
            speed = 0.5f;
            spawnRate = 4.0f;
            difficultyMultiplier = 2.5f;
            break;
        }
    }
    std::cout << spawnTime << std::endl;
}

void DifficultyManager::nextDifficulty() {
    switch (difficultyEnum) {
        case Difficulty::Easy:
            difficultyEnum = Difficulty::Medium;
        break;
        case Difficulty::Medium:
            difficultyEnum = Difficulty::Hard;
        break;
        case Difficulty::Hard:
            difficultyEnum = Difficulty::Extreme;
        break;
        case Difficulty::Extreme:
            difficultyEnum = Difficulty::Easy;
        break;
    }
    changeDifficulty();
}

Difficulty& DifficultyManager::getDifficulty() {
    return difficultyEnum;
}

float DifficultyManager::getDifficultyMultiplier() {
    return difficultyMultiplier;
};
