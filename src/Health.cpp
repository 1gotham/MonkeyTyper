//
// Created by gotham on 17.04.2025.
//

#include "Health.h"

#include "ScoreManager.h"

Health::Health(const sf::RenderWindow& window) {
    healthBarBackground.setSize({150.f, 30.f});
    healthBarBackground.setOrigin(sf::Vector2f(healthBarBackground.getSize().x / 2, healthBarBackground.getSize().y / 2));
    healthBarBackground.setPosition(sf::Vector2f(window.getSize().x / 2,  healthBarBackground.getSize().y));

    healthBar.setSize({140.f, 15.f});
    healthBar.setOrigin(sf::Vector2f(healthBar.getSize().x / 2, healthBar.getSize().y / 2));
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition(healthBarBackground.getPosition());

    damage = 10.f;
    healAmount = 2.0f;
    health = maxHealth;
}

void Health::takeDamage() {
    healthBar.setSize(sf::Vector2f(healthBar.getSize().x - damage, healthBar.getSize().y));
    health -= damage;
}

void Health::heal() {
    if (health < maxHealth) {
        healthBar.setSize(sf::Vector2f(healthBar.getSize().x + healAmount, healthBar.getSize().y));
        health += healAmount;
    }
}

void Health::drawHealthBar(sf::RenderWindow& window) {
    window.draw(healthBarBackground);
    window.draw(healthBar);
}

void Health::checkForDeath(GameStatus& gameStatus, ScoreManager& scoreManager, const std::string& playerName) {
    if (health <= 0) {
        scoreManager.saveScore(playerName);
        gameStatus = GameStatus::GameOver;
    }
}

void Health::resetHealth() {
    health = maxHealth;
    healthBar.setSize({140.f, 15.f});
}



