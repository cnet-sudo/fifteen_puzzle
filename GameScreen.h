#pragma once

#include "Screen.h"
#include "FifteenPuzzle.h"
#include "Button.h"
#include "ColorfulText.h"

class GameScreen : public Screen {
private:
    std::unique_ptr<FifteenPuzzle> puzzle;
    std::unique_ptr<Button> exitButton;
    std::unique_ptr<ColorfulText> titleText;
    sf::Text text;
    sf::RectangleShape textBackground;
    sf::Text timerText;
    sf::RectangleShape timerBackground;
    sf::Clock gameClock;
    bool isGameStarted;

    void initialize() override;

public:
    GameScreen(sf::RenderWindow& window, GameState& state, Transition& transition);
    void handleEvent(const sf::Event& event) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(float deltaTime) override;
    void restartGame();
};