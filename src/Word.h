//
// Created by gotham on 09.04.2025.
//

#ifndef WORD_H
#define WORD_H
#pragma once
#include <SFML/Graphics.hpp>

class Word {
    public:
        Word(const std::string &word, const sf::Font &font);

        void moveWord(float deltaTime, float speed);

        void draw(sf::RenderWindow &window) const;

        void setTextColor(const sf::Color& color);

        void highlightLetters(const std::string &typed);

        std::string getString() const;

        sf::Vector2f getPosition() const;

        sf::Text getText() const;

    private:
        sf::Text text;
        std::vector<sf::Text> characters;
        float x;
};



#endif //WORD_H
