#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "MainMenu.h"
#include "GameScreen.h"
#include "RulesScreen.h"

constexpr unsigned int WINDOW_WIDTH = 1280;
constexpr unsigned int WINDOW_HEIGHT = 720;
constexpr float MAX_DELTA_TIME = 1.0f / 30.0f; // Ограничение дельта-времени

int main() {
    try {
        // Создаем окно игры
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), L"Пятнашки");
        window.setFramerateLimit(60); // Ограничение FPS для плавности

        // Загружаем иконку
        sf::Image icon;
        if (!icon.loadFromFile("puzzle.png")) {
            throw std::runtime_error("Ошибка: не удалось загрузить puzzle.png!");
        }
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        // Создаем игровые экраны
        GameState state = GameState::MENU; // Начальное состояние
        Transition transition(window);
        GameScreen game(window, state, transition);
        MainMenu menu(window, state, transition,game);
       
        RulesScreen rules(window, state, transition);

        sf::Clock clock;

        while (window.isOpen()) {
            float deltaTime = clock.restart().asSeconds();
            if (deltaTime > MAX_DELTA_TIME) deltaTime = MAX_DELTA_TIME; // Ограничиваем резкие скачки

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                // Передаем событие текущему экрану
                switch (state) {
                case GameState::MENU:
                    menu.handleEvent(event);
                    break;
                case GameState::GAME:
                    game.handleEvent(event);
                    break;
                case GameState::RULES:
                    rules.handleEvent(event);
                    break;
                default:
                    break;
                }
            }

            // Обновляем переходы и текущий экран
            bool isTransitioning = transition.update(state, deltaTime); // Проверяем, идет ли переход
            switch (state) {
            case GameState::MENU:
                menu.update(deltaTime);
                break;
            case GameState::GAME:
                game.update(deltaTime);
                break;
            case GameState::RULES:
                rules.update(deltaTime); 
                break;
            default:
                break;
            }

            // Отрисовка
            window.clear();
            switch (state) {
            case GameState::MENU:
                window.draw(menu);
                break;
            case GameState::GAME:
                window.draw(game);
                break;
            case GameState::RULES:
                window.draw(rules);
                break;
            default:
                break;
            }
            // Отрисовываем переход поверх текущего экрана, если он активен
            if (isTransitioning) {
                window.draw(transition);
            }
            window.display();
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}