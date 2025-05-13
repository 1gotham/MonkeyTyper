//
// Created by gotham on 02.05.2025.
//

#include "OptionsBtn.h"
OptionsBtn::OptionsBtn(const sf::RenderWindow& windowArg, GameStatus& gameStatus) : btnTexture("gameSettingsBtn.png"){

}

void OptionsBtn::changeGameStatusOnClick(GameStatus& gameStatus, sf::RenderWindow& window){
    sf::FloatRect btnBounds = btnRect.getGlobalBounds();
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    if(btnBounds.contains(worldPos))
    {
        gameStatus = GameStatus::Options;
    }
};

void OptionsBtn::hoverOverBtn(sf::RenderWindow& window){
    sf::FloatRect btnBounds = btnRect.getGlobalBounds();
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    if(btnBounds.contains(worldPos))
    {
        btnRect.setOutlineColor(sf::Color(238,206,85));

    } else {
        btnRect.setOutlineColor(sf::Color::Transparent);
    }
};

void OptionsBtn::drawOptionsBtn(sf::RenderWindow& window){
    btnRect.setTexture(&btnTexture);
    btnRect.setSize(sf::Vector2f(210, 95));
    btnRect.setOutlineThickness(10);
    btnRect.setOrigin({btnRect.getSize().x / 2, btnRect.getSize().y / 2});
    btnRect.setPosition({960, 860});

    window.draw(btnRect);
    hoverOverBtn(window);
};