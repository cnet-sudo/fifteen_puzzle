#include "MainMenu.h"
#include <stdexcept>

constexpr float BUTTON_WIDTH = 500.0f;
constexpr float BUTTON_HEIGHT = 50.0f;
constexpr float SPACING = 30.0f;
constexpr float TITLE_Y_POS = 50.0f;

MainMenu::MainMenu(sf::RenderWindow& window, GameState& state, Transition& transition, GameScreen& gameScreen)
    : window(window), state(state), transition(transition), gameScreen(gameScreen), isMusicOn(true) {

    if (!font2.loadFromFile("glv.ttf")) throw std::runtime_error("Failed to load font glv.ttf");
    if (!font.loadFromFile("arial.ttf")) throw std::runtime_error("Failed to load font arial.ttf");

    useTexture = backgroundTexture.loadFromFile("background.png");
    if (useTexture) {
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        );
    }

    titleText = std::make_unique<ColorfulText>(font2, L"Пятнашки", 100,
        sf::Vector2f(0, TITLE_Y_POS), window, true, false);

    // Расчет позиции кнопок (теперь 5 кнопок)
    float startY = window.getSize().y / 2.0f - (5 * BUTTON_HEIGHT + 4 * SPACING) / 2.0f+50.0f; // Учитываем 5 кнопок
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

    if (!music.openFromFile("music.ogg")) throw std::runtime_error("Failed to load music.ogg");
    music.setLoop(true);
    music.play();
}

void MainMenu::update(float deltaTime) {
    titleText->update(deltaTime);
}

void MainMenu::handleEvent(const sf::Event& event) {
    sf::Vector2f mousePos(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y));

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
            if (isMusicOn && music.getStatus() != sf::Music::Playing) {
                music.play();
            }
            else if (!isMusicOn) {
                music.stop();
            }
        }
        if (restartButton->isClicked(mousePos)) {
            restartButton->releaseAnimation();
            gameScreen.restartGame();
            transition.startTransition(GameState::GAME); // Переключаемся на игру после рестарта
            
        }
        if (exitButton->isClicked(mousePos)) {
            exitButton->releaseAnimation();
            window.close(); // Закрытие окна
        }
    }
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (useTexture) {
        target.draw(backgroundSprite, states);
    }
    else {
        sf::RectangleShape background(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
        background.setFillColor(sf::Color::Cyan);
        target.draw(background, states);
    }

    titleText->draw(target, states);
    target.draw(*playButton, states);
    target.draw(*rulesButton, states);
    target.draw(*musicButton, states);
    target.draw(*restartButton, states); // Отрисовка кнопки "Рестарт"
    target.draw(*exitButton, states);    // Отрисовка кнопки "Выход"
}