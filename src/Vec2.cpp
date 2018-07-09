#define PI 3.14159265

#include "Vec2.h"

#include <math.h>

Vec2::Vec2() {
	x = 0;
	y = 0;
}

Vec2::Vec2(float x, float y) {
	Vec2::x = x;
	Vec2::y = y;
}

Vec2::~Vec2() {

}

bool Vec2::operator^=(const Vec2& rhs) const {
	if ((x > rhs.x - 20 && x < rhs.x + 20) && (y > rhs.y - 20 && y < rhs.y + 20))
		return true;
	else return false;
}

bool Vec2::operator!=(const Vec2& rhs) const {
	if (x != rhs.x || y != rhs.y)
		return true;
	else return false;
}

Vec2 Vec2::operator+(const Vec2& rhs) const {
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator+(const float rhs) const {
	return Vec2(x + rhs, y + rhs);
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator-(const float rhs) const {
	return Vec2(x - rhs, y - rhs);
}

Vec2 Vec2::operator*(const Vec2& rhs) const {
	return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator*(const float rhs) const {
	return Vec2(x * rhs, y * rhs);
}

Vec2 Vec2::operator/(const Vec2& rhs) const {
	return Vec2(x / rhs.x, y / rhs.y);
}

Vec2 Vec2::operator/(const float rhs) const {
	return Vec2(x / rhs, y / rhs);
}

Vec2 Vec2::Rotate(float ang) {
	return Vec2(x*Cos(ang) - y*Sin(ang), y*Cos(ang) + x*Sin(ang));
}

float Vec2::GetDX(float x) {
	return x-Vec2::x;
}

float Vec2::GetDY(float y) {
	return y-Vec2::y;
}

float Vec2::GetDS(Vec2 pos) {
	return pow(pow(GetDX(pos.x), 2)+pow(GetDY(pos.y), 2), 0.5);
}

float Vec2::GetCos(Vec2 pos) {
	return GetDX(pos.x)/GetDS(pos);
}

float Vec2::GetSin(Vec2 pos) {
	return GetDY(pos.y)/GetDS(pos);
}

float Vec2::GetAngle(Vec2 pos) {
	return 360-((int)(360-atan2(GetDY(pos.y), GetDX(pos.x))*(180/PI))%360);
}

float Vec2::Cos(float ang) {
	return cos(ang * PI/180);
}

float Vec2::Sin(float ang) {
	return sin(ang * PI/180);
}

Vec2 Vec2::Project(float dist, float ang) {
	return Vec2(Cos(ang) * dist, Sin(ang) * dist);
}
