#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Vec2.h"

#include <math.h>

class Circle {
public:
	float x;
	float y;
	float r;

	Circle();
	Circle(float x, float y, float r);
	~Circle();
	void SetPos(float x, float y);
	void SetPos(Vec2 pos);
	void SetRadius(float r);
	bool Contains(float a, float b);
	bool Contains(Vec2 p);
	Vec2 GetPos();
	float GetRadius();
	float Distance(float x1, float y1, float x2, float y2);
};

#endif 
