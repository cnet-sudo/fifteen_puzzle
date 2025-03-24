#pragma once

#include <SFML/Graphics.hpp>
#include "FifteenPuzzle.h"
#include "Button.h"
#include "ColorfulText.h"
#include "GameState.h"
#include "Transition.h"
#include <memory>

class GameScreen : public sf::Drawable {
private:
    sf::RenderWindow& window;
    GameState& state;
    Transition& transition;

    std::unique_ptr<FifteenPuzzle> puzzle;
    std::unique_ptr<Button> exitButton;
    std::unique_ptr<ColorfulText> titleText;
    sf::Text text;
    sf::RectangleShape textBackground;
    sf::Sprite backgroundSprite;
    sf::Text timerText;
    sf::RectangleShape timerBackground;
    sf::Clock gameClock;
    bool isGameStarted;

public:
    GameScreen(sf::RenderWindow& window, GameState& state, Transition& transition);
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(float deltaTime);
    void restartGame();
};