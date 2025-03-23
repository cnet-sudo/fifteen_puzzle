#include "RulesScreen.h"
#include <stdexcept>
#include <iostream>

constexpr float TITLE_Y_POS = 15.0f;

RulesScreen::RulesScreen(sf::RenderWindow& window, GameState& state, Transition& transition)
    : window(window), state(state), transition(transition) {
    // �������� �������� ����
    if (!backgroundTexture.loadFromFile("background1.png")) {
        std::cerr << "������: �� ������� ��������� ��� 'background1.png'.\n";
    }
    backgroundSprite.setTexture(backgroundTexture);

    // �������� ������ arial
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("�� ������� ��������� ����� arial.ttf");
    }

    // �������� ������ ��� ��������� (��� � GameScreen)
    if (!font2.loadFromFile("glv.ttf")) {
        throw std::runtime_error("�� ������� ��������� ����� glv.ttf");
    }

    // ��������� ��������� � ���������� �����
    titleText = std::make_unique<ColorfulText>(font2, L"������� ����", 100,
        sf::Vector2f(0, TITLE_Y_POS), window, true, false);

    // ��������� ������ � ��������� (������ ���� �������� �� �����������)
    text.setFont(font);
    text.setString(
        L"   1. ������� ���� ������� �� 15 ���������������\n" 
        L"   ������ � ������ ������� �����.\n"
		L"   2. ���� ���� ��������� ������, �����������\n"
        L"   �� � ���������� �������: (��. ����������� ������)\n"
        L"   3. ���������� ����� ������ ������,\n"
        L"   �������� � ������ ������.\n"
        L"   4. ����������� ��� ����������� ������ ����� ������\n"
        L"   ����.\n\n"
        L"   �����!"
    );
    text.setCharacterSize(30);  // ����������� ������ ������
    text.setFillColor(sf::Color::Black);

    // ������������� ������
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(0, text.getLocalBounds().height / 2.0f); // ������� ������������� �� X
    text.setPosition(30.0f, window.getSize().y / 2.0f ); // ������������� ����� � ������ ���� (20 �������� �� ����)

    // �������� ��������������� �������� ���� ��� �����
    textBackground.setSize(sf::Vector2f(textRect.width + 40, textRect.height + 60));
    textBackground.setFillColor(sf::Color(255, 255, 255, 200));
    textBackground.setOrigin(0, textBackground.getSize().y / 2.0f); // ������� ������������� �� X
    textBackground.setPosition(20.0f, window.getSize().y / 2.0f + 10.0f); // ������������� � �������

    // �������� ����������� � �������
    if (!numbersTexture.loadFromFile("numbers.png")) {
        std::cerr << "������: �� ������� ��������� ����������� 'numbers.png'.\n";
    }
    numbersSprite.setTexture(numbersTexture);
    sf::FloatRect numbersRect = numbersSprite.getLocalBounds();
    numbersSprite.setOrigin(numbersRect.width / 2.0f, numbersRect.height / 2.0f);
    // ���������� ����������� �� 10 % (������� 0.9)
        numbersSprite.setScale(0.9f, 0.9f);
    // �������� ������: ��������� ������� ����� � ������� ���� ����
    numbersSprite.setPosition(window.getSize().x * 0.75f+100, window.getSize().y / 2.0f );
    // �������� ������ � ����� GameScreen
    backButton = std::make_unique<Button>(
        std::wstring(L"� � � �"),
        sf::Vector2f(445, 600),
        font,
        sf::Color(64, 224, 208, 255),  // ��������� ����
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
    // ��������� ������� Esc ��� �������� � ����
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        transition.startTransition(GameState::MENU);
    }

    // ��������� ������� ������ ����
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (backButton->isClicked(mousePos)) {
            backButton->pressAnimation();
        }
    }

    // ��������� ���������� ������ ����
    if (event.type == sf::Event::MouseButtonReleased) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (backButton->isClicked(mousePos)) {
            backButton->releaseAnimation();
            transition.startTransition(GameState::MENU);
        }
    }
}

void RulesScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.clear(sf::Color::White);         // ������� ������ ����� ������
    target.draw(backgroundSprite, states);  // ��������� ������� ��������
    target.draw(textBackground, states);    // ��������� ��������������� ���� ��� �����
    target.draw(numbersSprite, states);     // ��������� ����������� � �������
    target.draw(text, states);             // ��������� ������ � ���������
    target.draw(*backButton, states);      // ��������� ������
    titleText->draw(target, states);       // ��������� ���������
}

void RulesScreen::update(float deltaTime) {
    titleText->update(deltaTime);  // ���������� �������� ���������
}