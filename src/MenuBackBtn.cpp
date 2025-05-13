//
// Created by gotham on 02.05.2025.
//

#include "MenuBackBtn.h"


MenuBackBtn::MenuBackBtn(const sf::RenderWindow& windowArg, GameStatus& gameStatus) : menuBackBtnTexture("menuBackBtn.png"), menuBackBtnTextureHover("menuBackbtnHover.png"){

}

void MenuBackBtn::changeGameStatusOnClick(GameStatus& gameStatus, sf::RenderWindow& window) {
    sf::FloatRect btnBounds = btnRect.getGlobalBounds();
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    if(btnBounds.contains(worldPos))
    {
        gameStatus = GameStatus::Menu;
    }
};

void MenuBackBtn::hoverOverBtn(sf::RenderWindow& window){
    sf::FloatRect btnBounds = btnRect.getGlobalBounds();
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    if(btnBounds.contains(worldPos))
    {
        btnRect.setTexture(&menuBackBtnTextureHover);

    } else {
        btnRect.setTexture(&menuBackBtnTexture);
    }
};

void MenuBackBtn::drawMenuBackBtn(sf::RenderWindow& window){
    btnRect.setSize(sf::Vector2f(128, 128));
    btnRect.setOrigin({btnRect.getSize().x / 2, btnRect.getSize().y / 2});
    btnRect.setPosition({960, 1080 - btnRect.getSize().y});

    window.draw(btnRect);
    hoverOverBtn(window);
};