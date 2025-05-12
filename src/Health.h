//
// Created by gotham on 17.04.2025.
//

#ifndef HEALTH_H
#define HEALTH_H
#include <SFML/Graphics.hpp>
#include "GameStatus.h"
#include "ScoreManager.h"


class Health {
    public:
        Health(const sf::RenderWindow& window);
        void takeDamage();
        void heal();
        void drawHealthBar(sf::RenderWindow& window);
        void checkForDeath(GameStatus& gameStatus, ScoreManager& scoreManager, const std::string& playerName);
        void resetHealth();
    private:
        const float maxHealth = 140.0f;
        float health;
        float damage;
        float healAmount;
        sf::RectangleShape healthBar;
        sf::RectangleShape healthBarBackground;
};



#endif //HEALTH_H
