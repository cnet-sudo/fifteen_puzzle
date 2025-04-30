#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

// �����, ����������� ���� "��������", ����������� �� sf::Drawable ��� ���������
class FifteenPuzzle : public sf::Drawable {
public:
    // ��������� �� ��������� ��� ������� ������ � �����
    static constexpr int DEFAULT_TILE_SIZE = 100;
    static constexpr int DEFAULT_GRID_SIZE = 4;

    // ����������� � ����������� ������� ������ � �����
    explicit FifteenPuzzle(int tileSize = DEFAULT_TILE_SIZE,
        int gridSize = DEFAULT_GRID_SIZE);
    // ���������� �� ���������
    ~FifteenPuzzle() = default;

    // ������ ����������� ��� �������������� ������������ ��������
    FifteenPuzzle(const FifteenPuzzle&) = delete;
    FifteenPuzzle& operator=(const FifteenPuzzle&) = delete;

    // ��������� ����������� ��� ��������� ��������� �����������
    FifteenPuzzle(FifteenPuzzle&&) = default;
    FifteenPuzzle& operator=(FifteenPuzzle&&) = default;

    // ��������� ������� ����� �� ������
    void setPosition(float x, float y);
    // ��������� ������� ������� �����
    sf::Vector2f getPosition() const;
    // ��������� ������ ����� (��� ��������� �������)
    sf::FloatRect getBounds() const;

    // ��������� ������� (��������, ������ ����)
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    // ���������� ��������� ���� (�������� ��� ��������� ��������)
    void update();
    // ��������, ����� �� ����
    bool isSolved() const;
    // ���������� ���� (������������� ������)
    void restart();

private:
    const int m_tileSize; // ������ ����� ������ (� ��������)
    const int m_gridSize; // ������ ����� (��������, 4x4)
    std::vector<std::vector<int>> m_board; // ��������� ������, �������������� ������� ����
    std::shared_ptr<sf::Font> m_font; // ����� ��� ����������� ������� ������
    int m_emptyX, m_emptyY; // ���������� ������ ������
    sf::Vector2f m_position; // ������� ����� �� ������
    bool m_isSolved; // ����, �����������, ����� �� ����

    // ������������� ������ ��� �������� ����� ����
    void shuffleBoard();
    // ��������, ����� �� ����������� ������ �� ��������� ����������
    bool canMove(int x, int y) const;
    // ����������� ������ �� ������ �����
    void moveTile(int x, int y);
    // ��������, �������� �� ������� ������������ ��������
    bool isSolvable(const std::vector<int>& numbers) const;
    // ����� ��������� ����� (��������������� sf::Drawable)
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};