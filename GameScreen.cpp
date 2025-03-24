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
    // �������� ��������� ResourceManager
    ResourceManager& rm = ResourceManager::getInstance();

    // ��������� ������� �� ResourceManager
    sf::Font& font = rm.getFont("font");    // �������������� "font" - ��� arial.ttf
    sf::Font& font2 = rm.getFont("font1");  // �������������� "font1" - ��� glv.ttf

    // �������� �������� �������� �������
    if (font.getInfo().family.empty()) {
        std::cerr << "������: �� ������� ��������� ����� 'font' �� ResourceManager.\n";
        throw std::runtime_error("�� ������� ��������� ����� 'font' �� ResourceManager");
    }
    if (font2.getInfo().family.empty()) {
        throw std::runtime_error("�� ������� ��������� ����� 'font1' �� ResourceManager");
    }

    // �������� �������� ���� �� ResourceManager
    sf::Texture& bgTexture = rm.getTexture("background1");
    if (bgTexture.getSize().x == 0) {  // �������� �� ������ ��������
        std::cerr << "������: �� ������� ��������� ��� 'background1' �� ResourceManager.\n";
    }
    backgroundSprite.setTexture(bgTexture);

    // ������� ������ "��������� � ������� ����"
    exitButton = std::make_unique<Button>(
        std::wstring(L"� � � �"),
        sf::Vector2f(445, 600),
        font,
        sf::Color(64, 224, 208, 255),  // ������������ ��������� ���� ������
        sf::Color(64, 224, 208, 255),
        sf::Color::Black,              // ���� ������
        sf::Color(128, 128, 128),      // ���� ������ ��� �������
        395.0f,                        // ������ ������
        50.0f,                         // ������ ������
        30u,                           // ������ ������
        sf::Color::Black,              // ���� �������
        4.0f                           // ������� �������
    );

    text.setFont(font);

    puzzle->setPosition(
        (window.getSize().x - puzzle->getBounds().width) / 2.0f,
        150.0f
    );

    // ������������� ��������� ����� ����� �����
    titleText = std::make_unique<ColorfulText>("font1", L"��������", 100,
        sf::Vector2f(0, TITLE_Y_POS), window, true, false);

    textBackground.setFillColor(sf::Color(255, 255, 255, 200)); // ����� � �������������

    // ��������� ������ �������
    timerText.setFont(font);
    timerText.setCharacterSize(45);
    timerText.setFillColor(sf::Color::Red);
    timerText.setPosition(
        puzzle->getBounds().left + puzzle->getBounds().width + 50.0f, // ������ �� ����
        puzzle->getBounds().top + 200.0f // ����� �� ����
    );

    // ��������� ���� �������
    timerBackground.setFillColor(sf::Color(255, 255, 255, 128)); // ����� � 50% �������������
    sf::FloatRect timerRect = timerText.getLocalBounds();
    timerBackground.setSize(sf::Vector2f(timerRect.width + 20.0f, timerRect.height + 40.0f)); // ������ 20 ��������
    timerBackground.setPosition(
        timerText.getPosition().x - 10.0f, // ��������� ������
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

    // ������ ������� ��� ������ �������������� � ������
    if (!isGameStarted && (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed)) {
        isGameStarted = true;
        gameClock.restart();
    }

    puzzle->handleEvent(event, window);

    if (puzzle->isSolved()) {
        text.setString(L"                   ������!!! \n"
            L"������� Esc ��� ������ ���� !");
        text.setFillColor(sf::Color::Red);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
        text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
        text.setCharacterSize(50);

        // ��������� ���� ��� �����
        textBackground.setSize(sf::Vector2f(textRect.width + 40, textRect.height + 40)); // ������ 40 ��������
        textBackground.setOrigin(textBackground.getSize().x / 2.0f, textBackground.getSize().y / 2.0f);
        textBackground.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    }

    // ������� ���� �� ������� R
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
        restartGame();
    }
}

void GameScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.clear(sf::Color::White);
    target.draw(backgroundSprite, states); // ������ ���
    target.draw(*puzzle, states);
    target.draw(textBackground, states);
    target.draw(text, states);
    target.draw(timerBackground, states); // ��������� ���� �������
    target.draw(timerText, states); // ��������� �������
    target.draw(*exitButton, states);
    titleText->draw(target, states);
}

void GameScreen::restartGame()
{
    puzzle->restart(); // ������������ ����� ������
    isGameStarted = false; // ������������� ������
    gameClock.restart();   // ���������� �����
    text.setString(L"");   // ������� ����� ������
    textBackground.setSize(sf::Vector2f(0, 0)); // �������� ���
}

void GameScreen::update(float deltaTime) {
    titleText->update(deltaTime);

    if (isGameStarted) {
        sf::Time elapsed = gameClock.getElapsedTime();
        int minutes = static_cast<int>(elapsed.asSeconds()) / 60;
        int seconds = static_cast<int>(elapsed.asSeconds()) % 60;
        int milliseconds = static_cast<int>(elapsed.asMilliseconds()) % 1000;

        std::wstring timerString = std::wstring(L"�����: ") +
            (minutes < 10 ? L"0" : L"") + std::to_wstring(minutes) + L":" +
            (seconds < 10 ? L"0" : L"") + std::to_wstring(seconds) + L":" +
            (milliseconds < 100 ? L"0" : (milliseconds < 10 ? L"00" : L"")) + std::to_wstring(milliseconds);
        timerText.setString(timerString);

        // ���������� �������� � ������� ���� ������� ��� ��������� ������
        sf::FloatRect timerRect = timerText.getLocalBounds();
        timerBackground.setSize(sf::Vector2f(timerRect.width + 20.0f, timerRect.height + 20.0f));
        timerBackground.setPosition(
            timerText.getPosition().x - 10.0f,
            timerText.getPosition().y
        );
    }
}