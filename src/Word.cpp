//
// Created by gotham on 09.04.2025.
//

#include "Word.h"
#include <random>
#include <SFML/Graphics.hpp>

Word::Word(const std::string &word, const sf::Font &font) : text(font, word, 150u), x(0){

  for (char character : text.getString()) {
    sf::Text letter(font, std::string(1, character), 35u);
    letter.setPosition(sf::Vector2f(x, 0));
    letter.setOutlineColor(sf::Color::Black);
    letter.setOutlineThickness(3);
    characters.push_back(letter);
    x += letter.getCharacterSize();
  }
  int min = 0;
  int max = 12;

  std::vector<float> positions = {100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700};
  int yPosIndex = std::rand() % (max - min + 1) + min;


  for (auto& character : characters) {
    character.setPosition(sf::Vector2f(0.f + character.getPosition().x, positions[yPosIndex]));
  }
}

void Word::moveWord(float deltaTime, float speed){
  for (auto& character : characters) {
    character.move(sf::Vector2f(speed * deltaTime, 0));
  }
}

void Word::draw(sf::RenderWindow &window) const {
  for (auto& character : characters) {
    window.draw(character);
  }
}

void Word::highlightLetters(const std::string& typed) {
  for (int i = 0; i < characters.size(); ++i) {
    if (i < typed.size()) {
      if (typed[i] == characters[i].getString()[0]) {
        characters[i].setFillColor(sf::Color(130, 217, 115));
      } else {
        characters[i].setFillColor(sf::Color::White);
      }
    } else {
      characters[i].setFillColor(sf::Color::White);
    }
  }
}

void Word::setTextColor(const sf::Color& color){
  text.setFillColor(color);
}

std::string Word::getString() const {
  return text.getString();
}

sf::Vector2f Word::getPosition() const {
  return characters[0].getPosition();
}

sf::Text Word::getText() const {
  return text;
}


