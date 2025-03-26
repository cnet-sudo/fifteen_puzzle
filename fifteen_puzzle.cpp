#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "MainMenu.h"
#include "GameScreen.h"
#include "RulesScreen.h"
#include "ResourceManager.h"
#include "Screen.h"
#include "resource.h"

constexpr unsigned int WINDOW_WIDTH = 1280;
constexpr unsigned int WINDOW_HEIGHT = 720;
constexpr float MAX_DELTA_TIME = 1.0f / 30.0f; // Ограничение дельта-времени

void initializeResources() {
    ResourceManager& rm = ResourceManager::getInstance();
    if (!rm.loadTexture("puzzle", IDR_TEXTURE1)) {
        throw std::runtime_error("Не удалось загрузить текстуру 'puzzle'");
    }
    if (!rm.loadTexture("background", IDR_TEXTURE2)) {
        throw std::runtime_error("Не удалось загрузить текстуру 'background'");
    }
    if (!rm.loadTexture("background1", IDR_TEXTURE3)) {
        throw std::runtime_error("Не удалось загрузить текстуру 'background1'");
    }
    if (!rm.loadTexture("background2", IDR_TEXTURE4)) {
        throw std::runtime_error("Не удалось загрузить текстуру 'background2'");
    }
    if (!rm.loadTexture("numbers", IDR_TEXTURE5)) {
        throw std::runtime_error("Не удалось загрузить текстуру 'numbers'");
    }
    if (!rm.loadMusic("music", IDR_SOUND1)) {
        throw std::runtime_error("Не удалось загрузить звук 'music'");
    }
    if (!rm.loadFont("font", IDR_FONT1)) {
        throw std::runtime_error("Не удалось загрузить шрифт 'font'");
    }
    if (!rm.loadFont("font1", IDR_FONT2)) {
        throw std::runtime_error("Не удалось загрузить шрифт 'font1'");
    }
}

int main() {
    system("chcp 1251"); // Установка кодовой страницы windows-1251 в консоли   
    try {
        initializeResources();

        // Создаем окно игры
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), L"Пятнашки");
        window.setFramerateLimit(60); // Ограничение FPS для плавности

        ResourceManager& rm = ResourceManager::getInstance();
        sf::Image icon = rm.getImage("puzzle");
        if (icon.getSize().x == 0 || icon.getSize().y == 0) { // Проверка, загружено ли изображение
            throw std::runtime_error("Ошибка: не удалось загрузить иконку 'puzzle' из ресурсов!");
        }
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        // Создаем игровые экраны
        GameState state = GameState::MENU; // Начальное состояние
        Transition transition(window);
        GameScreen gameScreen(window, state, transition);
        MainMenu mainMenu(window, state, transition, gameScreen);
        RulesScreen rulesScreen(window, state, transition);

        // Указатель на текущий экран
        Screen* currentScreen = &mainMenu;

        sf::Clock clock;

        while (window.isOpen()) {
            float deltaTime = clock.restart().asSeconds();
            if (deltaTime > MAX_DELTA_TIME) deltaTime = MAX_DELTA_TIME; // Ограничиваем резкие скачки

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                currentScreen->handleEvent(event); // Обрабатываем события текущего экрана
            }

            // Обновляем переходы и текущий экран
            bool isTransitioning = transition.update(state, deltaTime); // Проверяем, идет ли переход
            currentScreen->update(deltaTime); // Обновляем текущий экран

            // Отрисовка
            window.clear();
            window.draw(*currentScreen); // Рисуем текущий экран
            if (isTransitioning) {
                window.draw(transition); // Отрисовываем переход поверх экрана
            }
            window.display();

            // Переключение экранов на основе состояния
            switch (state) {
            case GameState::MENU:
                currentScreen = &mainMenu;
                break;
            case GameState::GAME:
                currentScreen = &gameScreen;
                break;
            case GameState::RULES:
                currentScreen = &rulesScreen;
                break;
            default:
                break;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}