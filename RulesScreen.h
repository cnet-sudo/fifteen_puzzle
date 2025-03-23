#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"
#include "Transition.h"
#include "ColorfulText.h"  // �������� ��������� ��� ColorfulText

class RulesScreen : public sf::Drawable {
public:
    // ����������� � �����������
    RulesScreen(sf::RenderWindow& window, GameState& state, Transition& transition);
    // ��������� �������
    void handleEvent(const sf::Event& event);
    // ���������� �������� ���������
    void update(float deltaTime);

private:
    // ���������������� ����� ���������
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RenderWindow& window;          // ������ �� ���� SFML
    GameState& state;                  // ������ �� ��������� ����
    Transition& transition;            // ������ �� ������ ��������

    sf::Font font;                     // ����� ��� ������ (arial)
    sf::Font font2;                    // ����� ��� ��������� (glv)
    sf::Text text;                    // ����� � ���������
    std::unique_ptr<ColorfulText> titleText; // ��������� � ���������� �����
    std::unique_ptr<Button> backButton; // ����� ��������� �� ������

    sf::Texture backgroundTexture;     // �������� ����
    sf::Sprite backgroundSprite;       // ������ ��� ����
    sf::RectangleShape textBackground; // ������������� ��� ��������������� ���� ������

    sf::Texture numbersTexture;        // �������� ��� ����������� � �������
    sf::Sprite numbersSprite;          // ������ ��� ����������� � �������
};

