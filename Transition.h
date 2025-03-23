#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"

class Transition : public sf::Drawable, public sf::Transformable {
public:
    Transition(sf::RenderWindow& window); // Конструктор с окном для динамического размера
    void startTransition(GameState newState);
    bool update(GameState& currentState, float deltaTime); // Добавляем deltaTime

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RectangleShape overlay;
    sf::RenderWindow& window; // Ссылка на окно для получения размера
    GameState targetState;
    float alpha; // Используем float для плавности
    bool transitioning;
    bool fadingIn; // Флаг для фазы fade-in
    float transitionDuration; // Длительность одной фазы
};