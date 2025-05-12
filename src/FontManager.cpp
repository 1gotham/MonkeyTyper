//
// Created by gotham on 07.05.2025.
//

#include "FontManager.h"

FontManager::FontManager(sf::Font defaultFont) : currentFont(defaultFont) {
    fonts = {sf::Font("Pacifico.ttf"), sf::Font("BebasNeue.ttf"), sf::Font("Roboto.ttf"), sf::Font("VCR.ttf"), sf::Font("Montserrat.ttf")};
    fontsNames = {"Pacifico","BebasNeue", "Roboto", "VCR", "Montserrat"};
    currentFontName = "VCR";

}

void FontManager::changeFont() {
    if (currentFontIndex < fonts.size() - 1) {
        currentFontIndex++;
    } else {
        currentFontIndex = 0;
    }
    currentFont = fonts[currentFontIndex];
    currentFontName = fontsNames[currentFontIndex];
}

sf::Font& FontManager::getCurrentFont() {
    return currentFont;
}

std::string FontManager::getCurrentFontName() {
    return currentFontName;
}

