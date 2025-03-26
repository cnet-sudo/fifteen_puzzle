// Screen.cpp
#include "Screen.h"
#include <iostream>

Screen::Screen(sf::RenderWindow& window, GameState& state, Transition& transition)
    : window(window), state(state), transition(transition), useTexture(false) {
}

void Screen::setupBackground(const std::string& textureId) {
    ResourceManager& rm = ResourceManager::getInstance();
    sf::Texture& bgTexture = rm.getTexture(textureId);
    if (bgTexture.getSize().x == 0) {
        std::cerr << "Ошибка: Не удалось загрузить текстуру фона '" << textureId << "' из ResourceManager.\n";
        useTexture = false;
    }
    else {
        useTexture = true;
        backgroundSprite.setTexture(bgTexture);
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / bgTexture.getSize().x,
            static_cast<float>(window.getSize().y) / bgTexture.getSize().y
        );
    }
}

