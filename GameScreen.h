#pragma once

#include <SFML/Graphics.hpp>
#include "FifteenPuzzle.h"
#include "Button.h"
#include "GameState.h"
#include "ColorfulText.h"
#include "Transition.h"

class GameScreen : public sf::Drawable {
public:
    // Конструктор, принимающий окно и состояние игры
    GameScreen(sf::RenderWindow& window, GameState& state, Transition& transition); // Добавляем Transition в конструктор
    void update(float deltaTime);
    // Обработка событий
    void handleEvent(const sf::Event& event);
    FifteenPuzzle* getPuzzle() { return puzzle.get(); } 
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void restartGame();
private:
    sf::RenderWindow& window;  // Ссылка на окно SFML
    GameState& state;         // Ссылка на текущее состояние игры
    Transition& transition; // Добавляем ссылку на Transition
    sf::Font font;            // Шрифт для текста
	sf::Font font2;		      // Шрифт для заголовка
    sf::Text text;           // Текст для отображения
    std::unique_ptr<FifteenPuzzle> puzzle;    // Экземпляр игры "Пятнашки"
    std::unique_ptr<Button> exitButton; // Кнопка "Вернуться в главное меню"  
    std::unique_ptr<ColorfulText> titleText;
    sf::Texture backgroundTexture; // Текстура фона
    sf::Sprite backgroundSprite;   // Спрайт фона
    sf::RectangleShape textBackground; // Полупрозрачный фон для текста
    sf::Text timerText;     // Текст таймера
    sf::Clock gameClock;    // Часы для отслеживания времени
    bool isGameStarted;
    sf::RectangleShape timerBackground; // Новый фон для таймера
};