//
// Created by gotham on 26.04.2025.
//

#ifndef PLAYBTN_H
#define PLAYBTN_H
#pragma once
#include "GameStatus.h"
#include <SFML/Graphics.hpp>



class PlayBtn {
    public:
        PlayBtn(const sf::RenderWindow& windowArg, GameStatus& gameStatus);
        void changeGameStatusOnClick(GameStatus& gameStatus);
        void drawPlayBtn(sf::RenderWindow& window);
        void hoverOverBtn(sf::RenderWindow& window);
    private:
        sf::RectangleShape btnRect;
        sf::Texture btnTexture;
};



#endif //PLAYBTN_H
