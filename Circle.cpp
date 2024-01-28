#include "Circle.h"

Circle::Circle(float r, size_t pC, Color col, Vector2f pos)
	: CircleShape(r, pC)
{
	setOrigin(r, r);
	setPosition(pos);
	setRadius(r);
	setFillColor(col);
}
