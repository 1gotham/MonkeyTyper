//
// Created by gotham on 17.04.2025.
//

#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H
#pragma once
#include "DifficultyManager.h"
#include "SFML/Graphics.hpp"
#include "Scoreboard.h"


class ScoreManager {
    public:
        ScoreManager(sf::RenderWindow& window, sf::Font &font, DifficultyManager& difficultyManager);
        void drawScore(sf::RenderWindow& window);
        void saveScore(const std::string &playerName);
        void addScore(std::string& currentWord);
        void drawScoreboard(sf::RenderWindow& window);
        void prepareScoreboard();

    private:
        int score = 0;
        sf::Text scoreText;
        Scoreboard scoreboard;
        sf::Font &font;
        DifficultyManager difficultyManager;

};



#endif //SCOREMANAGER_H
