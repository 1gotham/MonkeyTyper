//
// Created by gotham on 02.05.2025.
//

#include "Scoreboard.h"

Scoreboard::Scoreboard(const std::string& filename) : filename(filename) {}

void Scoreboard::load() {
    board.clear();
    std::ifstream inputFile(filename);
    if(!inputFile) return;

    Player p;
    while(inputFile >> p.name >> p.score){
        board.push_back(p);
    }
}

void Scoreboard::save() const {
    std::ofstream outputFile(filename);
    if(!outputFile){
        return;
    }
    for(const Player &p : board){
        outputFile << p.name << " " << p.score << std::endl;
    }
}

void Scoreboard::sort() {
    std::sort(board.begin(), board.end(), [](const Player& p1, const Player& p2) {
        return p1.score > p2.score;
    });
}

void Scoreboard::addPlayer(const std::string &name, int score) {
    board.push_back(Player{name, score});
}