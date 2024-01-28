#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;


class Circle : public CircleShape {
private:

public:
	Circle(float r = 1.f, size_t pC = 30, Color col = Color::Black, Vector2f pos = Vector2f(0.f, 0.f));
	~Circle()=default;
};

