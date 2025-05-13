//
// Created by gotham on 07.05.2025.
//

#include "OptionsManager.h"

#include <iostream>

OptionsManager::OptionsManager(sf::RenderWindow &window, FontManager& fontManager, DifficultyManager& difficultyManager, bool& musicOn, bool& wasMusicPlayed) : fontManager(fontManager), difficultyManager(difficultyManager), musicOn(musicOn), wasMusicPlayed(wasMusicPlayed) {

}

void OptionsManager::hoverOverOption(sf::RenderWindow &window) {
    for (int i = 0; i < optionsToChoose.size(); ++i) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
        if(optionsToChoose[i].getGlobalBounds().contains(worldPos))
        {
            optionsToChoose[i].setOutlineThickness(5);
            optionsToChoose[i].setOutlineColor(sf::Color(238,206,85));
            hoveredIndex = i;

        } else {
            optionsToChoose[i].setOutlineThickness(0);
        }
    }

}
void OptionsManager::changeOptionOnClick(sf::RenderWindow &window) {
    for (int i = 0; i < optionsToChoose.size(); ++i) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
        if(optionsToChoose[i].getGlobalBounds().contains(worldPos)){
            if (hoveredIndex == 0) {
                difficultyManager.nextDifficulty();
            } else if (hoveredIndex == 1) {
                fontManager.changeFont();
            } else if (hoveredIndex == 2) {
                musicOn = !musicOn;
                if (!musicOn) {
                    wasMusicPlayed = false;
                }
            }
        }
    }
}


void OptionsManager::makeOptions() {
    for (int i = 0; i < 3; ++i) {
        sf::Font& font = fontManager.getCurrentFont();
        sf::Text text(font);
        text.setPosition({100.f, 100.f + i*150.f});
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::White);
        optionsToChoose.push_back(text);
    }
    switch (difficultyManager.getDifficulty()) {
        case Difficulty::Easy: {
            optionsToChoose[0].setString("Difficulty: Easy [0.7x points]");
            break;
        }
        case Difficulty::Medium: {
            optionsToChoose[0].setString("Difficulty: Medium [1x points]");
            break;
        }
        case Difficulty::Hard: {
            optionsToChoose[0].setString("Difficulty: Hard [1.5x points]");
            break;
        }
        case Difficulty::Extreme: {
            optionsToChoose[0].setString("Difficulty: Extreme [2.5x points]");
            break;
        }
    }
    optionsToChoose[1].setString("Font: " + fontManager.getCurrentFontName());
    if (musicOn) {
        optionsToChoose[2].setString("Music: ON");
    } else {
        optionsToChoose[2].setString("Music: OFF");
    }
}

void OptionsManager::drawOptions(sf::RenderWindow& window) {
    optionsToChoose.clear();
    makeOptions();
    hoverOverOption(window);
    for (auto& option : optionsToChoose) {
        window.draw(option);
    }
}



