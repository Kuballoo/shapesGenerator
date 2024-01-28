#include <SFML/Graphics.hpp>

#include "Circle.h"

#include <iostream>

using namespace sf;
using namespace std;

void addShape(vector<Circle>& arr, Circle& shape, Vector2f pos);

void keyboardHandling();


// Below screenSize is declareted for fullscreen mode
//uint16_t screenSize[] { VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height};
uint16_t screenSize[]{ 1280, 720 };
RenderWindow window{ VideoMode(screenSize[0], screenSize[1]), "Shapes generator"/*, Style::Fullscreen*/ };
Event ev{};

vector<Circle> circles{};

int main()
{
    window.setFramerateLimit(60);
    
    bool press{ false }, drawOnMove{ false };
    Color color[]{ Color::Black, Color::White, Color::Red, Color::Green, Color::Blue, Color::Yellow };
    Color* selColor = color;
    float radius{1.f};
    Circle cs(radius, 30, *selColor);
    while (window.isOpen()) {

        while (window.pollEvent(ev)) {
            switch (ev.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                keyboardHandling();
                break;
            case Event::MouseButtonPressed:
                if (ev.key.code == Mouse::Button::Left) {
                    Vector2f pos{ static_cast<Vector2f>(Mouse::getPosition(window)) };
                    addShape(circles, cs, pos);
                    press = true;
                } else if (ev.key.code == Mouse::Button::Right) {
                    if (*selColor == color[(sizeof(color) / sizeof(Color) - 1)]) selColor = color;
                    else selColor++;
                    cs.setFillColor(*selColor);
                }
                break;
            case Event::MouseButtonReleased:
                if (ev.key.code == Mouse::Button::Left) press = false;
                else if (ev.key.code == Mouse::Button::Middle) drawOnMove = !drawOnMove;
                break;
            case Event::MouseMoved:
                if (press && drawOnMove) {
                    Vector2f pos{ static_cast<Vector2f>(Mouse::getPosition(window)) };
                    addShape(circles, cs, pos);
                }
                break;
            case Event::MouseWheelMoved:
                radius += (static_cast<float>(ev.mouseWheel.delta) / 10.f);
                if (radius <= 0.f) radius = 0.1f;
                cs.setRadius(radius);
                cs.setOrigin(radius, radius);
            }
        }


        window.clear(Color::White);
        for (auto circle : circles)
            window.draw(circle);
        
        window.display();
    }
    return 0;
}

void addShape(vector<Circle>& arr, Circle& shape, Vector2f pos) {
    shape.setPosition(pos);
    arr.push_back(shape);

    cout << "X circle pos: " << pos.x << "\tY circle pos: " << pos.y << endl;
    cout << "Circles count: " << arr.size() << endl;
    cout << "MB: " << static_cast<float>(sizeof(Circle) * arr.size()) / 1000000.f << endl;
}

void keyboardHandling() {
    if (ev.key.code == Keyboard::Escape)
        window.close();
    else if (ev.key.code == Keyboard::C)
        circles.clear();
}