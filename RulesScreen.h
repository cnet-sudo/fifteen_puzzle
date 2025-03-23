#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"
#include "Transition.h"
#include "ColorfulText.h"  // Добавлен заголовок для ColorfulText

class RulesScreen : public sf::Drawable {
public:
    // Конструктор с параметрами
    RulesScreen(sf::RenderWindow& window, GameState& state, Transition& transition);
    // Обработка событий
    void handleEvent(const sf::Event& event);
    // Обновление анимации заголовка
    void update(float deltaTime);

private:
    // Переопределенный метод отрисовки
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RenderWindow& window;          // Ссылка на окно SFML
    GameState& state;                  // Ссылка на состояние игры
    Transition& transition;            // Ссылка на объект перехода

    sf::Font font;                     // Шрифт для текста (arial)
    sf::Font font2;                    // Шрифт для заголовка (glv)
    sf::Text text;                    // Текст с правилами
    std::unique_ptr<ColorfulText> titleText; // Заголовок с изменением цвета
    std::unique_ptr<Button> backButton; // Умный указатель на кнопку

    sf::Texture backgroundTexture;     // Текстура фона
    sf::Sprite backgroundSprite;       // Спрайт для фона
    sf::RectangleShape textBackground; // Прямоугольник для полупрозрачного фона текста

    sf::Texture numbersTexture;        // Текстура для изображения с цифрами
    sf::Sprite numbersSprite;          // Спрайт для изображения с цифрами
};

