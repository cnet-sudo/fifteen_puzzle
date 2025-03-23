#pragma once

#include <SFML/Graphics.hpp>
#include "FifteenPuzzle.h"
#include "Button.h"
#include "GameState.h"
#include "ColorfulText.h"
#include "Transition.h"

class GameScreen : public sf::Drawable {
public:
    // �����������, ����������� ���� � ��������� ����
    GameScreen(sf::RenderWindow& window, GameState& state, Transition& transition); // ��������� Transition � �����������
    void update(float deltaTime);
    // ��������� �������
    void handleEvent(const sf::Event& event);
    FifteenPuzzle* getPuzzle() { return puzzle.get(); } 
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void restartGame();
private:
    sf::RenderWindow& window;  // ������ �� ���� SFML
    GameState& state;         // ������ �� ������� ��������� ����
    Transition& transition; // ��������� ������ �� Transition
    sf::Font font;            // ����� ��� ������
	sf::Font font2;		      // ����� ��� ���������
    sf::Text text;           // ����� ��� �����������
    std::unique_ptr<FifteenPuzzle> puzzle;    // ��������� ���� "��������"
    std::unique_ptr<Button> exitButton; // ������ "��������� � ������� ����"  
    std::unique_ptr<ColorfulText> titleText;
    sf::Texture backgroundTexture; // �������� ����
    sf::Sprite backgroundSprite;   // ������ ����
    sf::RectangleShape textBackground; // �������������� ��� ��� ������
    sf::Text timerText;     // ����� �������
    sf::Clock gameClock;    // ���� ��� ������������ �������
    bool isGameStarted;
    sf::RectangleShape timerBackground; // ����� ��� ��� �������
};