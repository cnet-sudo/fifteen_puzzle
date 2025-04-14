#include "FifteenPuzzle.h"
#include <numeric>
#include <iostream>
#include "ResourceManager.h"

FifteenPuzzle::FifteenPuzzle(int tileSize, int gridSize)
    : m_tileSize(tileSize)
    , m_gridSize(gridSize)
    , m_board(gridSize, std::vector<int>(gridSize))
    , m_font(std::make_unique<sf::Font>())
    , m_emptyX(0)
    , m_emptyY(0)
    , m_position(0.f, 0.f)
    , m_isSolved(false)
{
    ResourceManager& rm = ResourceManager::getInstance();
    m_font = std::make_shared<sf::Font>(rm.getFont("font"));
    
    if (m_font->getInfo().family.empty()) {
        throw std::runtime_error("Не удалось загрузить шрифт 'font' из ResourceManager");
    }
    shuffleBoard();
}

void FifteenPuzzle::setPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
}

sf::Vector2f FifteenPuzzle::getPosition() const {
    return m_position;
}

sf::FloatRect FifteenPuzzle::getBounds() const {
    return sf::FloatRect(m_position.x, m_position.y,
        m_tileSize * m_gridSize,
        m_tileSize * m_gridSize);
}

// Перемешивание плиток
void FifteenPuzzle::shuffleBoard() {
    std::vector<int> numbers(m_gridSize * m_gridSize);
    std::iota(numbers.begin(), numbers.end(), 1);
    numbers.back() = 0;

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);

    for (int i = 0; i < m_gridSize; ++i) {
        for (int j = 0; j < m_gridSize; ++j) {
            m_board[i][j] = numbers[i * m_gridSize + j];
            if (m_board[i][j] == 0) {
                m_emptyX = j;
                m_emptyY = i;
            }
        }
    }
    m_isSolved = false;
}

bool FifteenPuzzle::canMove(int x, int y) const {
    return (abs(x - m_emptyX) + abs(y - m_emptyY) == 1) &&
        (x >= 0 && x < m_gridSize && y >= 0 && y < m_gridSize);
}

// Передвижение плиток
void FifteenPuzzle::moveTile(int x, int y) {
    if (canMove(x, y)) {
        std::swap(m_board[m_emptyY][m_emptyX], m_board[y][x]);
        m_emptyX = x;
        m_emptyY = y;
        m_isSolved = isSolved();
    }
}

// Проверка на победу
bool FifteenPuzzle::isSolved() const {
    int expected = 1;
    for (const auto& row : m_board) {
        for (const auto& tile : row) {
            if (expected == m_gridSize * m_gridSize) {
                return tile == 0;
            }
            if (tile != expected++) {
                return false;
            }
        }
    }
    return true;
}

void FifteenPuzzle::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords(
            sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

        if (getBounds().contains(mousePos)) {
            int x = static_cast<int>((mousePos.x - m_position.x) / m_tileSize);
            int y = static_cast<int>((mousePos.y - m_position.y) / m_tileSize);
            moveTile(x, y);
        }
    }
}

void FifteenPuzzle::update() {
    // Обновление логики игры (если потребуется)
}


// Отрисовка поля и плиток
void FifteenPuzzle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.translate(m_position);

    for (int i = 0; i < m_gridSize; ++i) {
        for (int j = 0; j < m_gridSize; ++j) {
            if (m_board[i][j] != 0) {
                // Рисуем бирюзовую плитку
                sf::RectangleShape rect(sf::Vector2f(m_tileSize - 2, m_tileSize - 2));
                rect.setPosition(j * m_tileSize + 1, i * m_tileSize + 1);
                rect.setFillColor(sf::Color(64, 224, 208)); // Бирюзовый цвет
                target.draw(rect, states);

                if (m_font) {
                    sf::Text text;
                    text.setFont(*m_font);
                    text.setString(std::to_string(m_board[i][j]));
                    text.setCharacterSize(m_tileSize / 2); // Увеличенный размер шрифта
                    text.setFillColor(sf::Color::Black);

                    auto textRect = text.getLocalBounds();
                    text.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
                    text.setPosition(j * m_tileSize + m_tileSize / 2.0f,
                        i * m_tileSize + m_tileSize / 2.5f); // Коррекция центра
                    target.draw(text, states);
                }
            }
        }
    }

    
}

void FifteenPuzzle::restart() {
    shuffleBoard(); // Перемешиваем доску заново
}