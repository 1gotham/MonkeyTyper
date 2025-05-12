//
// Created by gotham on 07.05.2025.
//

#ifndef OPTIONSMANAGER_H
#define OPTIONSMANAGER_H
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "DifficultyManager.h"
#include "FontManager.h"

class OptionsManager {
    public:
        OptionsManager(sf::RenderWindow& window, FontManager& fontManager, DifficultyManager& difficultyManager, bool& musicOn, bool& wasMusicPlayed);
        void hoverOverOption(sf::RenderWindow& window);
        void drawOptions(sf::RenderWindow& window);
        void changeOptionOnClick();


    private:
        std::vector<sf::Text>optionsToChoose;
        void makeOptions();
        FontManager& fontManager;
        DifficultyManager& difficultyManager;
        int hoveredIndex;
        bool& musicOn;
        bool& wasMusicPlayed;
};



#endif //OPTIONSMANAGER_H
