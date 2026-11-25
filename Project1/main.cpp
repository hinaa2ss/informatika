#include <SFML/Graphics.hpp>
#include <functional>
#include <cmath>

// Функция для отрисовки графика
void drawGraph(sf::RenderWindow& window, std::function<float(float)> func, float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x); // Вычисление значения функции

        // Преобразование координат в экранные
        float screenX = 400 + x * scaleX;
        float screenY = 300 - y * scaleY;

        // Добавление точки в массив вершин
        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }

    window.draw(graph);
}

int main() {
    // Создание окна
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graphics");
    // Переменная для хранения пользовательской точки
    sf::CircleShape userPoint(5); // Радиус 5 пикселей
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false; // Переменная для проверки существования пользовательской точки

    // 1 _ Загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }
    // Текст для отображения координат точки и номера зоны
    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setPosition(10.0f, 10.0f);
    coordinatesText.setFillColor(sf::Color::White);
    coordinatesText.setString(
        L"Postav'te tochku levoy knopkoi mishi"
    );
    
    

    // Оси X и Y
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(0, 300); // Начало оси X
    xAxis[0].color = sf::Color::White; // Цвет оси
    xAxis[1].position = sf::Vector2f(800, 300); // Конец оси X
    xAxis[1].color = sf::Color::White;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 0); // Начало оси Y
    yAxis[0].color = sf::Color::White; // Цвет оси
    yAxis[1].position = sf::Vector2f(400, 600); // Конец оси Y
    yAxis[1].color = sf::Color::White;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Проверка клика мышью
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Получение позиции клика
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Преобразование экранных координат в "математические"
                    float mathX = (mousePos.x - 400) / 40.0f; // Масштаб 30 по X
                    float mathY = -(mousePos.y - 300) / 10.0f; // Масштаб 100 по Y

                    // Установка новой пользовательской точки
                    userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                    userPointExists = true; // Помечаем, что точка существует

                    // 3 Проверка нахождения пользовательской точки
                    float lineY = mathX + 9.0f; // Y прямой  в заданном X
                    float parabolaY = mathX * mathX; // Y параболы в заданном X
                    const float epsilon = 0.5f; // Нужно для того, чтобы при небольшой погрешности точка всё равно отмечалась как находящаяся на границе
                    std::string zone = "";

                    if (std::fabs(mathY - lineY) < epsilon ||
                        std::fabs(mathY - parabolaY) < epsilon) // Если модуль разности между Y точки и Y функции меньше epsilon, считаем что она на границе
                    {
                        zone = "Granitsa"; // точка на границе графика
                    }
                    else if (mathY > lineY && mathY > parabolaY)
                    {
                        zone = "5"; // выше обоих графиков
                    }
                    else if (mathY < lineY && mathY < parabolaY)
                    {
                        zone = "2"; // ниже обоих графиков
                    }
                    else
                    {
                        // Точки пересечения графиков (x*x = x + 9):
                        float x1 = (1.0f - std::sqrt(37.0f)) / 2.0f;
                        float x2 = (1.0f + std::sqrt(37.0f)) / 2.0f;

                        if (mathX < x1)
                            zone = "1";
                        else if (mathX < x2)
                            zone = "3";
                        else
                            zone = "4";
                    }


                    // Обновление текста с координатами точки и номером зоны
                    coordinatesText.setString("Coordinates: (" + std::to_string(mathX) + ", " + std::to_string(mathY) + ") \n Zone:" + zone);
                }
            }
        }


        // Очистка экрана
        window.clear(sf::Color(30, 30, 30));


        // Отрисовка осей
        window.draw(xAxis);
        window.draw(yAxis);



        // Отрисовка графика y1 = x + 9
        drawGraph(window, [](float x) { return x + 9.0f; }, -10, 10, 40, 10.0, sf::Color::Red);

        // Отрисовка графика y2 = x * x
        drawGraph(window, [](float x) { return x * x; }, -10, 10, 40, 10.0, sf::Color::Blue);

        // Отрисовка пользовательской точки, если она существует
        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
        }

        // Отображение нового кадра
        window.display();
    }

    return 0;
}