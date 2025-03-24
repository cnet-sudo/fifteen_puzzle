
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "GameState.h"
#include "Transition.h"
#include "ColorfulText.h"
#include <memory>
#include "GameScreen.h"

class MainMenu : public sf::Drawable {
private:
    sf::RenderWindow& window;
    GameState& state;
    Transition& transition;
    sf::Font font;
    sf::Font font2;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    std::unique_ptr<Button> playButton;
    std::unique_ptr<Button> rulesButton;
    std::unique_ptr<Button> musicButton;
    std::unique_ptr<Button> restartButton; 
    std::unique_ptr<Button> exitButton;    
    std::unique_ptr<ColorfulText> titleText;
    sf::Music* music;
    bool isMusicOn;
    bool useTexture;
    GameScreen& gameScreen; // Добавляем ссылку на GameScreen
public:
    MainMenu(sf::RenderWindow& window, GameState& state, Transition& transition, GameScreen& gameScreen);
    void update(float deltaTime);
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};





