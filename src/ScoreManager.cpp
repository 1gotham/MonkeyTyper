//
// Created by gotham on 17.04.2025.
//

#include "ScoreManager.h"
#include <fstream>

ScoreManager::ScoreManager(sf::RenderWindow &window, sf::Font &font, DifficultyManager& difficultyManager) : scoreText(font, "0", 70), score(0), scoreboard("scoreboard.txt"), font(font), difficultyManager(difficultyManager){
}

void ScoreManager::drawScore(sf::RenderWindow &window) {
    scoreText.setPosition({420, 870});
    window.draw(scoreText);
}


void ScoreManager::addScore(std::string& currentWord) {
    score += 100 * currentWord.size() * difficultyManager.getDifficultyMultiplier();
    scoreText.setString(std::to_string(score));
}

void ScoreManager::saveScore(const std::string &playerName) {
    scoreboard.load();
    scoreboard.addPlayer(playerName, score);
    scoreboard.sort();
    scoreboard.save();
    score = 0;
    scoreText.setString("0");
}

void ScoreManager::drawScoreboard(sf::RenderWindow &win) {
    const auto &board = scoreboard.getBoard();
    float x = 960;
    float y = 100.f;
    sf::Text title(font, "=== TOP 10 ===", 50);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin({titleBounds.size.x/2, titleBounds.size.y/2});
    title.setPosition({x, y});
    win.draw(title);
    y += 60.f;
    for (int i = 0; i < (int)board.size(); ++i) {
        if (i < 10) {
            const auto &p = board[i];
            sf::Text line(font, std::to_string(i+1) + ". " + p.name + " - " + std::to_string(p.score), 40);
            line.setFillColor({238, 193, 79});
            sf::FloatRect lineBounds = line.getLocalBounds();
            line.setOrigin({lineBounds.size.x/2, lineBounds.size.y/2});
            line.setPosition({x, y + i * 45.f});
            win.draw(line);
        }
    }
}

void ScoreManager::prepareScoreboard() {
    scoreboard.load();
    scoreboard.sort();
}
