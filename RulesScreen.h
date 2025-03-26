#pragma once

#include "Screen.h"
#include "Button.h"
#include "ColorfulText.h"

class RulesScreen : public Screen {
private:
    std::unique_ptr<ColorfulText> titleText;
    sf::Text text;
    sf::RectangleShape textBackground;
    sf::Sprite numbersSprite;
    std::unique_ptr<Button> backButton;

    void initialize() override;

public:
    RulesScreen(sf::RenderWindow& window, GameState& state, Transition& transition);
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

