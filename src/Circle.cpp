#include "Circle.h"



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

void Circle::SetPos(float x, float y) {
	Circle::x = x;
	Circle::y = y;
}

void Circle::SetPos(Vec2 pos) {
	x = pos.x;
	y = pos.y;
}

void Circle::SetRadius(float r) {
	Circle::r = r;
}

bool Circle::Contains(float a, float b) {
	return((a < x + r) && (b < y + r));
}

bool Circle::Contains(Vec2 p) {
	return((p.x < x+r) && (p.y < y + r));
}

Vec2 Circle::GetPos() {
	return Vec2(x, y);
}

float Circle::GetRadius() {
	return Circle::r;
}

float Circle::Distance(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
