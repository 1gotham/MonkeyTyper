//
// Created by gotham on 02.05.2025.
//

#ifndef OPTIONSBTN_H
#define OPTIONSBTN_H
#pragma once

#include "GameStatus.h"
#include <SFML/Graphics.hpp>


class OptionsBtn {
    public:
        OptionsBtn(const sf::RenderWindow& windowArg, GameStatus& gameStatus);
        void changeGameStatusOnClick(GameStatus& gameStatus, sf::RenderWindow& window);
        void drawOptionsBtn(sf::RenderWindow& window);
        void hoverOverBtn(sf::RenderWindow& window);
    private:
        sf::RectangleShape btnRect;
        sf::Texture btnTexture;
};



#endif //OPTIONSBTN_H
