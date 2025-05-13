#include <algorithm>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

#include "FontManager.h"
#include "Word.h"
#include "Health.h"
#include "ScoreManager.h"
#include "SFML/Audio.hpp"
#include "GameStatus.h"
#include "PlayBtn.h"
#include "MenuBackBtn.h"
#include "ScoreboardBtn.h"
#include "OptionsBtn.h"
#include "OptionsManager.h"




void handleTextEntered(auto& currentWord, auto& character, auto& inputText) {
    if (character == '\b' && !currentWord.empty()) {
        currentWord.pop_back();

    } else if (
        (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')){
        currentWord.push_back(character);
    }

    inputText.setString(currentWord);
}

void addPlayersName(auto& playersName, auto &character, auto& playersNameText) {
    if (character == '\b' && !playersName.empty()) {
        playersName.pop_back();

    } else if (
        (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')){
        playersName.push_back(character);
        }
    playersNameText.setString(playersName);
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

std::vector<std::string> loadWordsFromFile(const std::filesystem::path& filePath) {
    std::ifstream wordsFile(filePath);
    std::vector<std::string> wordList;
    auto word = std::string();
    while (wordsFile >> word) {
        wordList.push_back(word);
    }
    return wordList;
}


int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Monkey Typer");
    window.setFramerateLimit(144);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));


    sf::RectangleShape menuBackground;
    sf::Texture backgroundTexture("backgroundTexture.png");
    menuBackground.setSize(sf::Vector2f(1920u, 1080u));
    menuBackground.setTexture(&backgroundTexture);

    sf::RectangleShape playingBackground;
    sf::Texture playingTexture("playingBackground.png");
    playingBackground.setSize(sf::Vector2f(1920u, 1080u));
    playingBackground.setTexture(&playingTexture);

    sf::RectangleShape enteringNameBg;
    sf::Texture enteringNameBgTexture("enteringNameBg.png");
    enteringNameBg.setSize(sf::Vector2f(1920u, 1080u));
    enteringNameBg.setTexture(&enteringNameBgTexture);

    sf::RectangleShape scoreboardBg;
    sf::Texture scoreboardBgTexture("scoreboardBg.png");
    scoreboardBg.setSize(sf::Vector2f(1920u, 1080u));
    scoreboardBg.setTexture(&scoreboardBgTexture);

    float deltaTime;
    auto speed = 0.5f;
    auto spawnTime = 1.f;
    auto spawnRate = 1.f;
    sf::Clock clock;
    sf::Clock spawnClock;
    auto currentWordInput = std::string("");
    auto playerEnteredName = false;
    bool musicOn = true;
    bool wasMusicPlayed = false;

    // --------------------------------------------------------------
    Health health(window);
    GameStatus gameStatus = GameStatus::Menu;
    Difficulty difficultyEnum  = Difficulty::Medium;

    PlayBtn playBtn(window, gameStatus);
    MenuBackBtn menuBackBtn(window, gameStatus);
    ScoreboardBtn scoreboardBtn(window, gameStatus);
    OptionsBtn optionsBtn(window, gameStatus);

    FontManager fontManager(sf::Font("VCR.ttf"));
    DifficultyManager difficultyManager(difficultyEnum, spawnTime, speed, spawnRate);
    ScoreManager scoreManager(window, fontManager.getCurrentFont(), difficultyManager);
    OptionsManager optionsManager(window, fontManager, difficultyManager, musicOn, wasMusicPlayed);

    // --------------------------------------------------------------

    sf::Text inputText(fontManager.getCurrentFont());
    inputText.setPosition(sf::Vector2f(1320, 870));
    inputText.setCharacterSize(70);

    std::string playersName;
    sf::Text playersNameText(fontManager.getCurrentFont());
    playersNameText.setCharacterSize(70);

    playersNameText.setPosition(sf::Vector2f(window.getSize().x/2, 780));
    playersNameText.setFillColor(sf::Color::White);

    //--------------------------------------------------------------

    std::vector<Word> texts;
    std::vector<std::string> wordList = loadWordsFromFile("words.txt");

    //--------------------------------------------------------------
    sf::Music music;
    music.openFromFile("pjc_muzyka2.wav");
    music.setVolume(30);
    music.setLooping(true);
    //-------------------------------------------------------------- game over sound
    sf::SoundBuffer buffer;
    buffer.loadFromFile("christopher.wav");
    sf::Sound christopherSound(buffer);
    bool wasChristopherPlayed = false;

    //--------------------------------------------------------------


    auto spawnNewWords = [&texts, &wordList, &fontManager, &spawnClock, &spawnTime, &spawnRate]() {
        if (!wordList.empty()) {

            if (spawnClock.getElapsedTime().asSeconds() >= spawnTime) {
                for (int i = 0; i < spawnRate; ++i) {
                    std::string randomWord = wordList[rand() % wordList.size()];
                    Word wordGen(randomWord, fontManager.getCurrentFont());
                    texts.push_back(wordGen);
                    spawnClock.restart();
                }
            }
        }
    };

    auto removeWordFromInput = [&texts, &currentWordInput, &inputText, &health, &scoreManager]() {
        const auto it = std::ranges::find_if(texts, [currentWordInput](const Word &text) {
        return text.getString() == currentWordInput;
    });

        if (it != texts.end()) {
            scoreManager.addScore(currentWordInput);
            texts.erase(it);
            currentWordInput = "";
            inputText.setString(currentWordInput);
            health.heal();
        }
    };

    auto checkIfOutOfBounds = [&texts, &deltaTime, &speed, &window, &health]() {
        for (size_t i = 0; i < texts.size(); ) {
            texts[i].moveWord(deltaTime,speed);

            if (texts[i].getPosition().x > window.getSize().x) {
                texts.erase(texts.begin() + i);
                health.takeDamage();

            } else {
                ++i;
            }
        }
    };

    auto setBaseValues = [&health, &inputText, &currentWordInput, &playerEnteredName, &playersNameText, &playersName, &wasChristopherPlayed]() {
        health.resetHealth();
        inputText.setString("");
        currentWordInput = "";
        playerEnteredName = false;
        playersName = "";
        playersNameText.setString("");
        wasChristopherPlayed = false;
    };


    sf::Text gameOverText(fontManager.getCurrentFont(), "GAME OVER", 50);
    sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin({gameOverBounds.size.x/2, gameOverBounds.size.y/2});
    gameOverText.setPosition(sf::Vector2f{1920/2, 1080/2});

    while (window.isOpen()) {
        if (!wasMusicPlayed && musicOn) {
            music.play();
            wasMusicPlayed = true;
        } else if (!musicOn){
            music.stop();
        }
        switch (gameStatus) {
            case GameStatus::Menu:
            {
                window.draw(menuBackground);

                while (const std::optional event = window.pollEvent()) {
                    if (event->is<sf::Event::Closed>())
                    {
                        window.close();
                    }
                    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                    {
                        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                        {
                            setBaseValues();
                            scoreboardBtn.changeGameStatusOnClick(gameStatus, scoreManager, window);
                            playBtn.changeGameStatusOnClick(gameStatus, window);
                            optionsBtn.changeGameStatusOnClick(gameStatus, window);

                            spawnClock.restart();
                            clock.restart();
                        }
                    }
                }
                scoreboardBtn.drawScoreboardBtn(window);
                playBtn.drawPlayBtn(window);
                optionsBtn.drawOptionsBtn(window);
                break;
            }
            case GameStatus::Playing:
            {
                if (!playerEnteredName) {
                    while (const std::optional event = window.pollEvent()) {
                        if (event->is<sf::Event::Closed>())
                        {
                            window.close();
                        }
                        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                            if (keyPressed->scancode == sf::Keyboard::Scan::Enter) {
                                spawnClock.restart();
                                clock.restart();
                                playerEnteredName = true;
                            }
                        }
                        if (const auto* textEntered = event->getIf<sf::Event::TextEntered>())
                        {
                            sf::FloatRect playersNameRect = playersNameText.getLocalBounds();
                            playersNameText.setOrigin({playersNameRect.size.x/2, 0.f});
                            char character = static_cast<char>(textEntered->unicode);
                            addPlayersName(playersName, character, playersNameText);
                        }
                        if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                        {
                            if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                            {
                                menuBackBtn.changeGameStatusOnClick(gameStatus, window);
                            }
                        }
                    }
                    window.clear();
                    window.draw(enteringNameBg);
                    window.draw(playersNameText);
                    menuBackBtn.drawMenuBackBtn(window);
                } else {
                    while (const std::optional event = window.pollEvent())
                    {
                        if (event->is<sf::Event::Closed>())
                        {
                            window.close();
                        }
                        if (const auto* textEntered = event->getIf<sf::Event::TextEntered>())
                        {
                            char character = static_cast<char>(textEntered->unicode);
                            handleTextEntered(currentWordInput, character, inputText);
                            highlightCurrentWord(texts, currentWordInput);
                        }
                    }

                    deltaTime = clock.restart().asMilliseconds();
                    checkIfOutOfBounds();
                    health.checkForDeath(gameStatus, scoreManager, playersName);
                    if (gameStatus == GameStatus::Playing) {
                        spawnNewWords();
                        removeWordFromInput();
                    }

                    window.clear();
                    window.draw(playingBackground);
                    for (auto &textT : texts) {
                        textT.draw(window);
                    }
                    window.draw(inputText);
                    scoreManager.drawScore(window);
                    health.drawHealthBar(window);
                }
                break;
            }
            case GameStatus::ShowScores:
            {
                while (const std::optional event = window.pollEvent()) {
                    if (event->is<sf::Event::Closed>())
                    {
                        window.close();
                    }
                    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                    {
                        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                        {
                            menuBackBtn.changeGameStatusOnClick(gameStatus, window);
                        }
                    }
                }
                window.clear();
                window.draw(scoreboardBg);
                scoreManager.drawScoreboard(window);
                menuBackBtn.drawMenuBackBtn(window);
                break;
            }
            case GameStatus::Options: {
                while (const std::optional event = window.pollEvent()) {
                    if (event->is<sf::Event::Closed>())
                    {
                        window.close();
                    }
                    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                    {
                        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                        {
                            menuBackBtn.changeGameStatusOnClick(gameStatus, window);
                            optionsManager.changeOptionOnClick(window);
                        }
                    }
                }
                window.clear();
                window.draw(scoreboardBg);
                optionsManager.drawOptions(window);
                menuBackBtn.drawMenuBackBtn(window);
                break;
            }
            case GameStatus::GameOver:
            {
                texts.clear();
                music.stop();
                wasMusicPlayed = false;

                if (!wasChristopherPlayed) {
                    christopherSound.play();
                    wasChristopherPlayed = true;
                }
                window.clear();
                while (const std::optional event = window.pollEvent()) {
                    if (event->is<sf::Event::Closed>())
                    {
                        window.close();
                    }
                    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                    {
                        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                        {
                            menuBackBtn.changeGameStatusOnClick(gameStatus, window);
                            spawnClock.restart();
                            clock.restart();
                        }
                    }
                }
                window.draw(scoreboardBg);
                window.draw(gameOverText);
                menuBackBtn.drawMenuBackBtn(window);
                break;
            }
        }
        window.display();
    }
    return 0;
}