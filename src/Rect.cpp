#include "Rect.h"

Rect::Rect() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

Rect::Rect(float x, float y, float w, float h) {
	Rect::x = x;
	Rect::y = y;
	Rect::w = w;
	Rect::h = h;
}

Rect::~Rect() {

}

void Rect::SetPos(float x, float y) {
	Rect::x = x;
	Rect::y = y;
}

void Rect::SetPos(Vec2 pos) {
	x = pos.x;
	y = pos.y;
}

void Rect::SetSize(float w, float h) {
	Rect::w = w;
	Rect::h = h;
}

void Rect::SetSize(Vec2 size) {
	w = size.x;
	h = size.y;
}

void Rect::SetCenter(float x, float y) {
	Rect::x = x-(w/2);
	Rect::y = y-(h/2);
}

void Rect::SetCenter(Vec2 pos) {
	x = pos.x-(w/2);
	y = pos.y-(h/2);
}

bool Rect::Contains(float a, float b) {
	return((a > x) && (a < x+w) && (b > y) && (b < y+h));
}

bool Rect::Contains(Vec2 p) {
	return((p.x > x) && (p.x < x+w) && (p.y > y) && (p.y < y+h));
}

Vec2 Rect::GetPos() {
	return Vec2(x, y);
}

Vec2 Rect::GetSize() {
	return Vec2(w, h);
}

Vec2 Rect::GetCenter() {
	return Vec2(x+(w/2),y+(h/2));
}
