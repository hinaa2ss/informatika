#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Setka");
    window.setFramerateLimit(60);

    const int cellSize = 50;
    const int gridSize = 10;

    // Массив для хранения ячеек
    sf::RectangleShape cells[gridSize][gridSize];

    // Инициализируем ячейки вложенными циклами
    for (int i = 0; i < gridSize; ++i)
    {
        for (int j = 0; j < gridSize; ++j)
        {
            cells[i][j].setSize(sf::Vector2f(cellSize - 2, cellSize - 2)); // размер ячейки
            cells[i][j].setPosition(i * cellSize, j * cellSize);           // позиция из индексов
            cells[i][j].setFillColor(sf::Color::White);                    // цвет заливки
            cells[i][j].setOutlineColor(sf::Color::Black);                 // цвет границы
            cells[i][j].setOutlineThickness(0.6);
        }
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        for (int i = 0; i < gridSize; ++i)
        {
            for (int j = 0; j < gridSize; ++j)
            {
                if (i + j < gridSize - 1) {
                    cells[i][j].setFillColor(sf::Color::Green);
                }
                window.draw(cells[i][j]);
            }
        }
        window.display();
    }
    return 0;
}