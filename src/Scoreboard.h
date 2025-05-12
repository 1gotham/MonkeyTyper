//
// Created by gotham on 02.05.2025.
//

#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

//Scoreboard z pomocą ChatGPT

struct Player {
    std::string name;
    int score;
};

class Scoreboard {
    public:
        Scoreboard(const std::string& filename);
        void load();
        void save() const;
        void addPlayer(const std::string& name, int score);
        void sort();

        const std::vector<Player>& getBoard() const { return board; }
    private:
        std::vector<Player> board;
        std::string filename;
};



#endif //SCOREBOARD_H
