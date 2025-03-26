#include "RulesScreen.h"
#include <stdexcept>
#include <iostream>

constexpr float TITLE_Y_POS = 15.0f;

RulesScreen::RulesScreen(sf::RenderWindow& window, GameState& state, Transition& transition)
    : Screen(window, state, transition) {
    initialize();
}

void RulesScreen::initialize() {
    ResourceManager& rm = ResourceManager::getInstance();
    sf::Font& font = rm.getFont("font");

    if (font.getInfo().family.empty()) {
        throw std::runtime_error("Не удалось загрузить шрифт 'font' из ResourceManager");
    }

    setupBackground("background1");

    titleText = std::make_unique<ColorfulText>("font1", L"Пятнашки", 100,
        sf::Vector2f(0, TITLE_Y_POS), window, true, false);

    text.setFont(font);
    text.setString(
        L"   1. Игровое поле состоит из 15 пронумерованных\n"
        L"   плиток и одного пустого места.\n"
        L"   2. Цель игры перемещая плитки, расположить\n"
        L"   их в правильном порядке: (см. изображение справа)\n"
        L"   3. Перемещать можно только плитки,\n"
        L"   соседние с пустым местом.\n"
        L"   4. Используйте для перемещения плиток левую кнопку\n"
        L"   мыши.\n\n"
        L"   Удачи!"
    );
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(0, text.getLocalBounds().height / 2.0f);
    text.setPosition(30.0f, window.getSize().y / 2.0f);

    textBackground.setSize(sf::Vector2f(textRect.width + 40, textRect.height + 60));
    textBackground.setFillColor(sf::Color(255, 255, 255, 200));
    textBackground.setOrigin(0, textBackground.getSize().y / 2.0f);
    textBackground.setPosition(20.0f, window.getSize().y / 2.0f + 10.0f);

    sf::Texture& numTexture = rm.getTexture("numbers");
    if (numTexture.getSize().x == 0) {
        std::cerr << "Ошибка: Не удалось загрузить изображение 'numbers' из ResourceManager.\n";
    }
    numbersSprite.setTexture(numTexture);
    sf::FloatRect numbersRect = numbersSprite.getLocalBounds();
    numbersSprite.setOrigin(numbersRect.width / 2.0f, numbersRect.height / 2.0f);
    numbersSprite.setScale(0.9f, 0.9f);
    numbersSprite.setPosition(window.getSize().x * 0.75f + 100, window.getSize().y / 2.0f);

    backButton = std::make_unique<Button>(
        std::wstring(L"м е н ю"),
        sf::Vector2f(445, 600),
        font,
        sf::Color(64, 224, 208, 255),
        sf::Color(64, 224, 208, 255),
        sf::Color::Black,
        sf::Color(128, 128, 128),
        395.0f,
        50.0f,
        30u,
        sf::Color::Black,
        4.0f
    );
}

void RulesScreen::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        transition.startTransition(GameState::MENU);
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (backButton->isClicked(mousePos)) {
            backButton->pressAnimation();
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (backButton->isClicked(mousePos)) {
            backButton->releaseAnimation();
            transition.startTransition(GameState::MENU);
        }
    }
}

void RulesScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.clear(sf::Color::White);
    if (useTexture) {
        target.draw(backgroundSprite, states);
    }
    target.draw(textBackground, states);
    target.draw(numbersSprite, states);
    target.draw(text, states);
    target.draw(*backButton, states);
    titleText->draw(target, states);
}

void RulesScreen::update(float deltaTime) {
    titleText->update(deltaTime);
}