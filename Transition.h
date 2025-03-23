#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"

class Transition : public sf::Drawable, public sf::Transformable {
public:
    Transition(sf::RenderWindow& window); // ����������� � ����� ��� ������������� �������
    void startTransition(GameState newState);
    bool update(GameState& currentState, float deltaTime); // ��������� deltaTime

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RectangleShape overlay;
    sf::RenderWindow& window; // ������ �� ���� ��� ��������� �������
    GameState targetState;
    float alpha; // ���������� float ��� ���������
    bool transitioning;
    bool fadingIn; // ���� ��� ���� fade-in
    float transitionDuration; // ������������ ����� ����
};