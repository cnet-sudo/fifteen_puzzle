#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

// Класс, реализующий игру "Пятнашки", наследуется от sf::Drawable для отрисовки
class FifteenPuzzle : public sf::Drawable {
public:
    // Константы по умолчанию для размера плитки и сетки
    static constexpr int DEFAULT_TILE_SIZE = 100;
    static constexpr int DEFAULT_GRID_SIZE = 4;

    // Конструктор с параметрами размера плитки и сетки
    explicit FifteenPuzzle(int tileSize = DEFAULT_TILE_SIZE,
        int gridSize = DEFAULT_GRID_SIZE);
    // Деструктор по умолчанию
    ~FifteenPuzzle() = default;

    // Запрет копирования для предотвращения дублирования ресурсов
    FifteenPuzzle(const FifteenPuzzle&) = delete;
    FifteenPuzzle& operator=(const FifteenPuzzle&) = delete;

    // Разрешено перемещение для поддержки семантики перемещения
    FifteenPuzzle(FifteenPuzzle&&) = default;
    FifteenPuzzle& operator=(FifteenPuzzle&&) = default;

    // Установка позиции пазла на экране
    void setPosition(float x, float y);
    // Получение текущей позиции пазла
    sf::Vector2f getPosition() const;
    // Получение границ пазла (для обработки событий)
    sf::FloatRect getBounds() const;

    // Обработка событий (например, кликов мыши)
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    // Обновление состояния игры (заглушка для возможных анимаций)
    void update();
    // Проверка, решён ли пазл
    bool isSolved() const;
    // Перезапуск игры (перемешивание плиток)
    void restart();

private:
    const int m_tileSize; // Размер одной плитки (в пикселях)
    const int m_gridSize; // Размер сетки (например, 4x4)
    std::vector<std::vector<int>> m_board; // Двумерный массив, представляющий игровое поле
    std::shared_ptr<sf::Font> m_font; // Шрифт для отображения номеров плиток
    int m_emptyX, m_emptyY; // Координаты пустой плитки
    sf::Vector2f m_position; // Позиция пазла на экране
    bool m_isSolved; // Флаг, указывающий, решён ли пазл

    // Перемешивание плиток для создания новой игры
    void shuffleBoard();
    // Проверка, можно ли переместить плитку на указанные координаты
    bool canMove(int x, int y) const;
    // Перемещение плитки на пустое место
    void moveTile(int x, int y);
    // Проверка, является ли текущая конфигурация решаемой
    bool isSolvable(const std::vector<int>& numbers) const;
    // Метод отрисовки пазла (переопределение sf::Drawable)
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};