#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Transition.h"
#include "Button.h"
#include "ColorfulText.h"
#include <memory>

class RulesScreen : public sf::Drawable {
private:
    sf::RenderWindow& window;
    GameState& state;
    Transition& transition;

    sf::Sprite backgroundSprite;
    std::unique_ptr<ColorfulText> titleText;
    sf::Text text;
    sf::RectangleShape textBackground;
    sf::Sprite numbersSprite;
    std::unique_ptr<Button> backButton;

public:
    RulesScreen(sf::RenderWindow& window, GameState& state, Transition& transition);
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(float deltaTime);
};

