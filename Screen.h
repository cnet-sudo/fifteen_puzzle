#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Transition.h"
#include "ResourceManager.h"
#include <memory>

class Screen : public sf::Drawable {
protected:
    sf::RenderWindow& window;
    GameState& state;
    Transition& transition;

    // Общие элементы интерфейса
    sf::Sprite backgroundSprite;
    bool useTexture;

    Screen(sf::RenderWindow& window, GameState& state, Transition& transition);

    // Виртуальные методы для настройки ресурсов и элементов интерфейса
    virtual void initialize() = 0;

    // Вспомогательные методы
    void setupBackground(const std::string& textureId);

public:
    virtual ~Screen() = default;

    // Общие методы, которые будут переопределяться
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

