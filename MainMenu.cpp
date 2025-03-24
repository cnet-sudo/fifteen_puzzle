#include "MainMenu.h"
#include <stdexcept>
#include "ResourceManager.h"
#include <iostream>

constexpr float BUTTON_WIDTH = 500.0f;  // Ширина кнопки
constexpr float BUTTON_HEIGHT = 50.0f;  // Высота кнопки
constexpr float SPACING = 30.0f;        // Расстояние между кнопками
constexpr float TITLE_Y_POS = 50.0f;    // Позиция заголовка по Y

// Конструктор главного меню
MainMenu::MainMenu(sf::RenderWindow& window, GameState& state, Transition& transition, GameScreen& gameScreen)
    : window(window), state(state), transition(transition), gameScreen(gameScreen), isMusicOn(true) {

    // Получаем экземпляр менеджера ресурсов
    ResourceManager& rm = ResourceManager::getInstance();

    // Используем шрифты из менеджера ресурсов с проверкой
    sf::Font& font2 = rm.getFont("font1");  // "font1" соответствует glv.ttf
    sf::Font& font = rm.getFont("font");    // "font" соответствует arial.ttf

    // Проверка успешной загрузки шрифтов
    if (font2.getInfo().family.empty() || font.getInfo().family.empty()) {
        throw std::runtime_error("Не удалось получить шрифты из ResourceManager");
    }

    // Загружаем текстуру фона из менеджера ресурсов
    useTexture = true;
    sf::Texture& backgroundTexture = rm.getTexture("background");
    if (backgroundTexture.getSize().x == 0) {  // Проверка на пустую текстуру
        useTexture = false;
        std::cerr << "Не удалось загрузить текстуру фона, используется запасной фон" << std::endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,  // Масштабируем по ширине
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y   // Масштабируем по высоте
        );
    }

    // Создаем анимированный заголовок
    titleText = std::make_unique<ColorfulText>("font1", L"Пятнашки", 100,
        sf::Vector2f(0, TITLE_Y_POS), window, true, false);

    // Расчет позиций кнопок
    float startY = window.getSize().y / 2.0f - (5 * BUTTON_HEIGHT + 4 * SPACING) / 2.0f + 50.0f; // Начальная позиция Y
    float centerX = (window.getSize().x - BUTTON_WIDTH) / 2.0f;  // Центр по X

    // Создаем кнопки
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

    // Получаем музыку из ResourceManager
    music = &rm.getMusic("music");
    if (music->getStatus() == sf::Music::Stopped && music->getDuration() == sf::Time::Zero) {
        throw std::runtime_error("Музыкальный поток не инициализирован в ResourceManager");
    }
    music->setLoop(true);  // Устанавливаем зацикливание
    music->play();         // Запускаем воспроизведение
}

// Обновление состояния меню
void MainMenu::update(float deltaTime) {
    titleText->update(deltaTime);  // Обновляем анимацию заголовка
}

// Обработка событий
void MainMenu::handleEvent(const sf::Event& event) {
    sf::Vector2f mousePos(static_cast<float>(sf::Mouse::getPosition(window).x),
        static_cast<float>(sf::Mouse::getPosition(window).y));

    // Обработка нажатия кнопки мыши
    if (event.type == sf::Event::MouseButtonPressed) {
        if (playButton->isClicked(mousePos)) playButton->pressAnimation();
        if (rulesButton->isClicked(mousePos)) rulesButton->pressAnimation();
        if (musicButton->isClicked(mousePos)) musicButton->pressAnimation();
        if (restartButton->isClicked(mousePos)) restartButton->pressAnimation();
        if (exitButton->isClicked(mousePos)) exitButton->pressAnimation();
    }

    // Обработка отпускания кнопки мыши
    if (event.type == sf::Event::MouseButtonReleased) {
        if (playButton->isClicked(mousePos)) {
            playButton->releaseAnimation();
            transition.startTransition(GameState::GAME);  // Переход к игре
        }
        if (rulesButton->isClicked(mousePos)) {
            rulesButton->releaseAnimation();
            transition.startTransition(GameState::RULES);  // Переход к правилам
        }
        if (musicButton->isClicked(mousePos)) {
            musicButton->releaseAnimation();
            isMusicOn = !isMusicOn;  // Переключение состояния музыки
            musicButton->setText(isMusicOn ? L"Музыка: Вкл" : L"Музыка: Выкл");
            if (isMusicOn && music->getStatus() != sf::Music::Playing) {
                music->play();  // Воспроизведение музыки
            }
            else if (!isMusicOn) {
                music->stop();  // Остановка музыки
            }
        }
        if (restartButton->isClicked(mousePos)) {
            restartButton->releaseAnimation();
            gameScreen.restartGame();  // Перезапуск игры
            transition.startTransition(GameState::GAME);  // Переход к игре
        }
        if (exitButton->isClicked(mousePos)) {
            exitButton->releaseAnimation();
            window.close();  // Закрытие окна
        }
    }
}

// Отрисовка меню
void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (useTexture) {
        target.draw(backgroundSprite, states);  // Отрисовка фона с текстурой
    }
    else {
        sf::RectangleShape background(sf::Vector2f(static_cast<float>(window.getSize().x),
            static_cast<float>(window.getSize().y)));
        background.setFillColor(sf::Color::Cyan);  // Запасной фон
        target.draw(background, states);
    }

    titleText->draw(target, states);      // Отрисовка заголовка
    target.draw(*playButton, states);     // Отрисовка кнопки "Играть"
    target.draw(*rulesButton, states);    // Отрисовка кнопки "Правила"
    target.draw(*musicButton, states);    // Отрисовка кнопки "Музыка"
    target.draw(*restartButton, states);  // Отрисовка кнопки "Рестарт"
    target.draw(*exitButton, states);     // Отрисовка кнопки "Выход"
}