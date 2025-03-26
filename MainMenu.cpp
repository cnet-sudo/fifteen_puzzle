#include "MainMenu.h"
#include <stdexcept>

constexpr float BUTTON_WIDTH = 500.0f;
constexpr float BUTTON_HEIGHT = 50.0f;
constexpr float SPACING = 30.0f;
constexpr float TITLE_Y_POS = 50.0f;

MainMenu::MainMenu(sf::RenderWindow& window, GameState& state, Transition& transition, GameScreen& gameScreen)
    : Screen(window, state, transition), gameScreen(gameScreen), isMusicOn(true) {
    initialize();
}

void MainMenu::initialize() {
    ResourceManager& rm = ResourceManager::getInstance();
    sf::Font& font = rm.getFont("font");
    sf::Font& font2 = rm.getFont("font1");

    if (font.getInfo().family.empty() || font2.getInfo().family.empty()) {
        throw std::runtime_error("Не удалось получить шрифты из ResourceManager");
    }

    setupBackground("background");

    titleText = std::make_unique<ColorfulText>("font1", L"Пятнашки", 100,
        sf::Vector2f(0, TITLE_Y_POS), window, true, false);

    float startY = window.getSize().y / 2.0f - (5 * BUTTON_HEIGHT + 4 * SPACING) / 2.0f + 50.0f;
    float centerX = (window.getSize().x - BUTTON_WIDTH) / 2.0f;

    playButton = std::make_unique<Button>(L"Играть", sf::Vector2f(centerX, startY), font,
        sf::Color(255, 192, 203, 150), sf::Color(255, 192, 203, 200), sf::Color::Blue,
        sf::Color(128, 128, 128), BUTTON_WIDTH, BUTTON_HEIGHT, 30, sf::Color::Magenta, 5.0f);

    rulesButton = std::make_unique<Button>(L"Правила", sf::Vector2f(centerX, startY + BUTTON_HEIGHT + SPACING), font,
        sf::Color(255, 192, 203, 150), sf::Color(255, 192, 203, 200), sf::Color::Blue,
        sf::Color(128, 128, 128), BUTTON_WIDTH, BUTTON_HEIGHT, 30, sf::Color::Magenta, 5.0f);

    musicButton = std::make_unique<Button>(L"Музыка: Вкл", sf::Vector2f(centerX, startY + 2 * (BUTTON_HEIGHT + SPACING)), font,
        sf::Color(255, 192, 203, 150), sf::Color(255, 192, 203, 200), sf::Color::Blue,
        sf::Color(128, 128, 128), BUTTON_WIDTH, BUTTON_HEIGHT, 30, sf::Color::Magenta, 5.0f);

    restartButton = std::make_unique<Button>(L"Рестарт", sf::Vector2f(centerX, startY + 3 * (BUTTON_HEIGHT + SPACING)), font,
        sf::Color(255, 192, 203, 150), sf::Color(255, 192, 203, 200), sf::Color::Blue,
        sf::Color(128, 128, 128), BUTTON_WIDTH, BUTTON_HEIGHT, 30, sf::Color::Magenta, 5.0f);

    exitButton = std::make_unique<Button>(L"Выход", sf::Vector2f(centerX, startY + 4 * (BUTTON_HEIGHT + SPACING)), font,
        sf::Color(255, 192, 203, 150), sf::Color(255, 192, 203, 200), sf::Color::Blue,
        sf::Color(128, 128, 128), BUTTON_WIDTH, BUTTON_HEIGHT, 30, sf::Color::Magenta, 5.0f);

    music = &rm.getMusic("music");
    if (music->getStatus() == sf::Music::Stopped && music->getDuration() == sf::Time::Zero) {
        throw std::runtime_error("Музыкальный поток не инициализирован в ResourceManager");
    }
    music->setLoop(true);
    music->play();
}

void MainMenu::update(float deltaTime) {
    titleText->update(deltaTime);
}

void MainMenu::handleEvent(const sf::Event& event) {
    sf::Vector2f mousePos(static_cast<float>(sf::Mouse::getPosition(window).x),
        static_cast<float>(sf::Mouse::getPosition(window).y));

    if (event.type == sf::Event::MouseButtonPressed) {
        if (playButton->isClicked(mousePos)) playButton->pressAnimation();
        if (rulesButton->isClicked(mousePos)) rulesButton->pressAnimation();
        if (musicButton->isClicked(mousePos)) musicButton->pressAnimation();
        if (restartButton->isClicked(mousePos)) restartButton->pressAnimation();
        if (exitButton->isClicked(mousePos)) exitButton->pressAnimation();
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        if (playButton->isClicked(mousePos)) {
            playButton->releaseAnimation();
            transition.startTransition(GameState::GAME);
        }
        if (rulesButton->isClicked(mousePos)) {
            rulesButton->releaseAnimation();
            transition.startTransition(GameState::RULES);
        }
        if (musicButton->isClicked(mousePos)) {
            musicButton->releaseAnimation();
            isMusicOn = !isMusicOn;
            musicButton->setText(isMusicOn ? L"Музыка: Вкл" : L"Музыка: Выкл");
            if (isMusicOn && music->getStatus() != sf::Music::Playing) {
                music->play();
            }
            else if (!isMusicOn) {
                music->stop();
            }
        }
        if (restartButton->isClicked(mousePos)) {
            restartButton->releaseAnimation();
            gameScreen.restartGame();
            transition.startTransition(GameState::GAME);
        }
        if (exitButton->isClicked(mousePos)) {
            exitButton->releaseAnimation();
            window.close();
        }
    }
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (useTexture) {
        target.draw(backgroundSprite, states);
    }
    else {
        sf::RectangleShape background(sf::Vector2f(static_cast<float>(window.getSize().x),
            static_cast<float>(window.getSize().y)));
        background.setFillColor(sf::Color::Cyan);
        target.draw(background, states);
    }

    titleText->draw(target, states);
    target.draw(*playButton, states);
    target.draw(*rulesButton, states);
    target.draw(*musicButton, states);
    target.draw(*restartButton, states);
    target.draw(*exitButton, states);
}