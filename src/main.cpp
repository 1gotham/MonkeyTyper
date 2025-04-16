#include <algorithm>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Word.h"


void handleTextEntered(auto& currentWord, auto& character, auto& inputText) {
    if (character == '\b' && !currentWord.empty()) {
        currentWord.pop_back();
    } else if (
        (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')){
        currentWord.push_back(character);
    }

    inputText.setString(currentWord);
}

void highlightCurrentWord(std::vector<Word>& texts, const std::string& currentWord) {
    for (auto& word : texts) {
        if (word.getString().starts_with(currentWord) && !currentWord.empty()) {
           word.highlightLetters(currentWord);
        } else {
            word.highlightLetters("");
        }
    }
}

int main()
{


    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Monkey Typer");
    window.setFramerateLimit(144);

    //--------------------------------------------------------------

    sf::Font font("Roboto.ttf");
    sf::Text text(font);
    float deltaTime;

    //--------------------------------------------------------------

    auto speed = 0.5f;
    auto spawnTime = 2.5f;
    sf::Clock clock;
    sf::Clock spawnClock;
    auto currentWord = std::string("");

    //--------------------------------------------------------------

    sf::Text inputText(font);
    inputText.setPosition(sf::Vector2f(1000, 500));
    inputText.setCharacterSize(40);

    //--------------------------------------------------------------

    auto counter = 0;
    sf::Text textCounter(font);
    textCounter.setPosition(sf::Vector2f(1000, 700));
    textCounter.setCharacterSize(30);
    textCounter.setString("0");

    //--------------------------------------------------------------

    auto score = 0;
    sf::Text textScore(font);
    textScore.setPosition(sf::Vector2f(1000, 200));
    textScore.setCharacterSize(40);
    textScore.setString("0");

    std::vector<Word> texts;

//--------------------------------------------------------------

    std::ifstream wordsFile("words.txt");
    std::vector<std::string> wordList;
    if (!wordsFile) {
        std::cerr << "Error opening file" << std::endl;
    } else {
        std::string word;
        while (wordsFile >> word) {
            wordList.push_back(word);
        }
    }


//--------------------------------------------------------------
    auto spawnNewWords = [&texts, &wordList, &font, &window, &spawnClock, &spawnTime]() {
        if (!wordList.empty()) {

            if (spawnClock.getElapsedTime().asSeconds() >= spawnTime) {
                std::string randomWord = wordList[rand() % wordList.size()];
                texts.emplace_back(randomWord, font, window.getSize().y);
                spawnClock.restart();
            }
        }
    };

    auto removeWordFromInput = [&texts, &currentWord, &inputText, & spawnTime, &score, &counter, &textScore]() {
        const auto it = std::find_if(texts.begin(), texts.end(), [currentWord](const Word &text) {
        return text.getString() == currentWord;
    });

        if (it != texts.end()) {
            score += 100 * currentWord.size();
            textScore.setString(std::to_string(score));
            texts.erase(it);
            currentWord = "";
            inputText.setString(currentWord);
            if (spawnTime > 0.6f) {
                spawnTime -= 0.05f;
                std::cout << spawnTime << std::endl;
            }

        }
    };

    auto checkIfOutOfBounds = [&texts, &deltaTime, &counter, &speed, &textCounter, &window]() {
        for (size_t i = 0; i < texts.size(); ) {
            texts[i].update(deltaTime,speed);

            if (texts[i].getPosition().x > window.getSize().x) {
                counter++;
                textCounter.setString(std::to_string(counter));
                texts.erase(texts.begin() + i);


            } else {
                ++i;
            }
        }
    };

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (const auto* textEntered = event->getIf<sf::Event::TextEntered>())
            {
                char character = static_cast<char>(textEntered->unicode);
                handleTextEntered(currentWord, character, inputText);
                highlightCurrentWord(texts, currentWord);
            }

        }

        spawnNewWords();

        removeWordFromInput();

        deltaTime = clock.restart().asMilliseconds();
        checkIfOutOfBounds();



        window.clear();
        for (auto &text : texts) {
            text.draw(window);
        }
        window.draw(inputText);
        window.draw(textCounter);
        window.draw(textScore);
        window.display();
    }
}

