#include "GameScreen.h"
#include <iostream>
#include <string>
#include "ResourceManager.h"

constexpr float TITLE_Y_POS = 15.0f;

GameScreen::GameScreen(sf::RenderWindow& window, GameState& state, Transition& transition)
    : window(window)
    , state(state)
    , transition(transition)
    , puzzle(std::make_unique<FifteenPuzzle>(100, 4))
    , isGameStarted(false)
{
    // Получаем экземпляр ResourceManager
    ResourceManager& rm = ResourceManager::getInstance();

    // Получение шрифтов из ResourceManager
    sf::Font& font = rm.getFont("font");    // Предполагается "font" - это arial.ttf
    sf::Font& font2 = rm.getFont("font1");  // Предполагается "font1" - это glv.ttf

    // Проверка успешной загрузки шрифтов
    if (font.getInfo().family.empty()) {
        std::cerr << "Ошибка: Не удалось загрузить шрифт 'font' из ResourceManager.\n";
        throw std::runtime_error("Не удалось загрузить шрифт 'font' из ResourceManager");
    }
    if (font2.getInfo().family.empty()) {
        throw std::runtime_error("Не удалось загрузить шрифт 'font1' из ResourceManager");
    }

    // Загрузка текстуры фона из ResourceManager
    sf::Texture& bgTexture = rm.getTexture("background1");
    if (bgTexture.getSize().x == 0) {  // Проверка на пустую текстуру
        std::cerr << "Ошибка: Не удалось загрузить фон 'background1' из ResourceManager.\n";
    }
    backgroundSprite.setTexture(bgTexture);

    // Создаем кнопку "Вернуться в главное меню"
    exitButton = std::make_unique<Button>(
        std::wstring(L"м е н ю"),
        sf::Vector2f(445, 600),
        font,
        sf::Color(64, 224, 208, 255),  // Непрозрачный бирюзовый цвет кнопки
        sf::Color(64, 224, 208, 255),
        sf::Color::Black,              // Цвет текста
        sf::Color(128, 128, 128),      // Цвет текста при нажатии
        395.0f,                        // Ширина кнопки
        50.0f,                         // Высота кнопки
        30u,                           // Размер шрифта
        sf::Color::Black,              // Цвет контура
        4.0f                           // Толщина контура
    );

    text.setFont(font);

    puzzle->setPosition(
        (window.getSize().x - puzzle->getBounds().width) / 2.0f,
        150.0f
    );

    // Инициализация заголовка через новый класс
    titleText = std::make_unique<ColorfulText>("font1", L"Пятнашки", 100,
        sf::Vector2f(0, TITLE_Y_POS), window, true, false);

    textBackground.setFillColor(sf::Color(255, 255, 255, 200)); // Белый с прозрачностью

    // Настройка текста таймера
    timerText.setFont(font);
    timerText.setCharacterSize(45);
    timerText.setFillColor(sf::Color::Red);
    timerText.setPosition(
        puzzle->getBounds().left + puzzle->getBounds().width + 50.0f, // Справа от поля
        puzzle->getBounds().top + 200.0f // Вверх от поля
    );

    // Настройка фона таймера
    timerBackground.setFillColor(sf::Color(255, 255, 255, 128)); // Белый с 50% прозрачностью
    sf::FloatRect timerRect = timerText.getLocalBounds();
    timerBackground.setSize(sf::Vector2f(timerRect.width + 20.0f, timerRect.height + 40.0f)); // Отступ 20 пикселей
    timerBackground.setPosition(
        timerText.getPosition().x - 10.0f, // Учитываем отступ
        timerText.getPosition().y
    );
}

void GameScreen::handleEvent(const sf::Event& event) {
    sf::Vector2f mousePos = window.mapPixelToCoords(
        sf::Vector2i(event.mouseButton.x, event.mouseButton.y)
    );

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        transition.startTransition(GameState::MENU);
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (exitButton->isClicked(mousePos)) {
            exitButton->pressAnimation();
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (exitButton->isClicked(mousePos)) {
            exitButton->releaseAnimation();
            transition.startTransition(GameState::MENU);
        }
    }

    // Запуск таймера при первом взаимодействии с пазлом
    if (!isGameStarted && (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed)) {
        isGameStarted = true;
        gameClock.restart();
    }

    puzzle->handleEvent(event, window);

    if (puzzle->isSolved()) {
        text.setString(L"                   Победа!!! \n"
            L"Нажмите Esc или кнопку меню !");
        text.setFillColor(sf::Color::Red);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
        text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
        text.setCharacterSize(50);

        // Настройка фона под текст
        textBackground.setSize(sf::Vector2f(textRect.width + 40, textRect.height + 40)); // Отступ 40 пикселей
        textBackground.setOrigin(textBackground.getSize().x / 2.0f, textBackground.getSize().y / 2.0f);
        textBackground.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    }

    // Рестарт игры по клавише R
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
        restartGame();
    }
}

void GameScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.clear(sf::Color::White);
    target.draw(backgroundSprite, states); // Рисуем фон
    target.draw(*puzzle, states);
    target.draw(textBackground, states);
    target.draw(text, states);
    target.draw(timerBackground, states); // Отрисовка фона таймера
    target.draw(timerText, states); // Отрисовка таймера
    target.draw(*exitButton, states);
    titleText->draw(target, states);
}

void GameScreen::restartGame()
{
    puzzle->restart(); // Перемешиваем доску заново
    isGameStarted = false; // Останавливаем таймер
    gameClock.restart();   // Сбрасываем время
    text.setString(L"");   // Убираем текст победы
    textBackground.setSize(sf::Vector2f(0, 0)); // Скрываем фон
}

void GameScreen::update(float deltaTime) {
    titleText->update(deltaTime);

    if (isGameStarted) {
        sf::Time elapsed = gameClock.getElapsedTime();
        int minutes = static_cast<int>(elapsed.asSeconds()) / 60;
        int seconds = static_cast<int>(elapsed.asSeconds()) % 60;
        int milliseconds = static_cast<int>(elapsed.asMilliseconds()) % 1000;

        std::wstring timerString = std::wstring(L"Время: ") +
            (minutes < 10 ? L"0" : L"") + std::to_wstring(minutes) + L":" +
            (seconds < 10 ? L"0" : L"") + std::to_wstring(seconds) + L":" +
            (milliseconds < 100 ? L"0" : (milliseconds < 10 ? L"00" : L"")) + std::to_wstring(milliseconds);
        timerText.setString(timerString);

        // Обновление размеров и позиции фона таймера при изменении текста
        sf::FloatRect timerRect = timerText.getLocalBounds();
        timerBackground.setSize(sf::Vector2f(timerRect.width + 20.0f, timerRect.height + 20.0f));
        timerBackground.setPosition(
            timerText.getPosition().x - 10.0f,
            timerText.getPosition().y
        );
    }
}