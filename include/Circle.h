#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Vec2.h"

class Circle {
public:
	float x;
	float y;
	float r;

	Circle();
	Circle(float x, float y, float r);
	~Circle();
	void SetCenter(float x, float y);
	void SetCenter(Vec2 pos);
	void SetRadius(float r);
	bool Contains(float a, float b);
	bool Contains(Vec2 p);
	Vec2 GetCenter();
};

#endif /* CIRCLE_H_ */