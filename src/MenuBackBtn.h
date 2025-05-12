//
// Created by gotham on 02.05.2025.
//

#ifndef MENUBACKBTN_H
#define MENUBACKBTN_H
#pragma once

#include <SFML/Graphics.hpp>
#include "GameStatus.h"



class MenuBackBtn {
    public:
        MenuBackBtn(const sf::RenderWindow& windowArg, GameStatus& gameStatus);
        void changeGameStatusOnClick(GameStatus& gameStatus);
        void drawMenuBackBtn(sf::RenderWindow& window);
        void hoverOverBtn(sf::RenderWindow& window);
    private:
        sf::RectangleShape btnRect;
        sf::Texture menuBackBtnTexture;
        sf::Texture menuBackBtnTextureHover;
};



#endif //MENUBACKBTN_H
