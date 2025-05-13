//
// Created by gotham on 26.04.2025.
//

#include "PlayBtn.h"
#include <iostream>

PlayBtn::PlayBtn(const sf::RenderWindow& window, GameStatus& gameStatus) : btnTexture("playBtnTexture.png"){
}

void PlayBtn::changeGameStatusOnClick(GameStatus& gameStatus, sf::RenderWindow& window) {
        sf::FloatRect btnBounds = btnRect.getGlobalBounds();
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
        if(btnBounds.contains(worldPos))
        {
                gameStatus = GameStatus::Playing;
        }
}

void PlayBtn::drawPlayBtn(sf::RenderWindow& window) {
        btnRect.setSize(sf::Vector2f(210, 95));
        btnRect.setOrigin({btnRect.getSize().x / 2, btnRect.getSize().y / 2});
        btnRect.setPosition({960, 540});
        btnRect.setTexture(&btnTexture);
        window.draw(btnRect);
        hoverOverBtn(window);
}

void PlayBtn::hoverOverBtn(sf::RenderWindow& window) {
        sf::FloatRect btnBounds = btnRect.getGlobalBounds();
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
        if(btnBounds.contains(worldPos))
        {
                btnRect.setOutlineThickness(10);
                btnRect.setOutlineColor(sf::Color(238,206,85));

        } else {
                btnRect.setOutlineColor(sf::Color::Transparent);
        }
}

