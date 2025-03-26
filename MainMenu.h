
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "GameState.h"
#include "Transition.h"
#include "ColorfulText.h"
#include <memory>
#include "GameScreen.h"
#include "Screen.h"

class MainMenu : public Screen {
private:
    std::unique_ptr<ColorfulText> titleText;
    std::unique_ptr<Button> playButton;
    std::unique_ptr<Button> rulesButton;
    std::unique_ptr<Button> musicButton;
    std::unique_ptr<Button> restartButton;
    std::unique_ptr<Button> exitButton;

    sf::Music* music;
    GameScreen& gameScreen;
    bool isMusicOn;

    void initialize() override;

public:
    MainMenu(sf::RenderWindow& window, GameState& state, Transition& transition, GameScreen& gameScreen);
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};





