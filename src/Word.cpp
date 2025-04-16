//
// Created by gotham on 09.04.2025.
//

#include "Word.h"
#include <random>
#include <SFML/Graphics.hpp>

Word::Word(const std::string &word, const sf::Font &font, unsigned int windowHeight) : text(font, word, 15), x(0){

  for (char character : text.getString()) {
    sf::Text letter(font, character, 15);
    letter.setPosition(sf::Vector2f(x, 0));
    characters.push_back(letter);
    x += 15;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(50, windowHeight - 50);
  auto randY = distrib(gen);


  float yPos = static_cast<float>(distrib(gen));
  for (auto& character : characters) {
    character.setPosition(sf::Vector2f(0.f + character.getPosition().x, yPos));
  }
}

void Word::update(float deltaTime, float speed){
  for (auto& character : characters) {
    character.move(sf::Vector2f(speed * deltaTime / text.getString().getSize(), 0));
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
        characters[i].setFillColor(sf::Color::Green);
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
  return text.getPosition();
}

sf::Text Word::getText() const {
  return text;
}


