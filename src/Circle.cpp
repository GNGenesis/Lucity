#include "Circle.h"

#include <math.h>

Circle::Circle() {
	x = 0;
	y = 0;
	r = 1;
}

Circle::Circle(float x, float y, float r) {
	Circle::x = x;
	Circle::y = y;
	Circle::r = r;
}

Circle::~Circle() {

}

void Circle::SetCenter(float x, float y) {
	Circle::x = x;
	Circle::y = y;
}

void Circle::SetCenter(Vec2 pos) {
	x = pos.x;
	y = pos.y;
}

void Circle::SetRadius(float r) {
	Circle::r = r;
}

bool Circle::Contains(float a, float b) {
	return((a < x+r && a > x-r) && (b < y+r && b > y-r));
}

bool Circle::Contains(Vec2 p) {
	return((p.x < x+r && p.x > x-r) && (p.y < y+r && p.y > y-r));
}

Vec2 Circle::GetCenter() {
	return Vec2(x, y);
}
