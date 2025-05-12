//
// Created by gotham on 07.05.2025.
//

#ifndef FONTMANAGER_H
#define FONTMANAGER_H
#pragma once
#include <SFML/Graphics.hpp>
#include <string>



class FontManager {
  public:
    FontManager(sf::Font defaultFont);
    sf::Font& getCurrentFont();
    std::string getCurrentFontName();
    void changeFont();


  private:
    sf::Font currentFont;
    std::string currentFontName;
    std::vector<sf::Font> fonts;
    std::vector<std::string> fontsNames;
    int currentFontIndex;

};



#endif //FONTMANAGER_H
