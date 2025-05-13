//
// Created by gotham on 02.05.2025.
//

#ifndef SCOREBOARDBTN_H
#define SCOREBOARDBTN_H
#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatus.h"
#include "ScoreManager.h"


class ScoreboardBtn {
    public:
        ScoreboardBtn(const sf::RenderWindow& windowArg, GameStatus& gameStatus);
        void changeGameStatusOnClick(GameStatus& gameStatus, ScoreManager& scoreManager, sf::RenderWindow& window);
        void drawScoreboardBtn(sf::RenderWindow& window);
        void hoverOverBtn(sf::RenderWindow& window);
    private:
        sf::RectangleShape btnRect;
        sf::Texture btnTexture;
};



#endif //SCOREBOARDBTN_H
