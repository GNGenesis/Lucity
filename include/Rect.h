#ifndef RECT_H_
#define RECT_H_

#include "Vec2.h"

class Rect {
public:
	float x;
	float y;
	float w;
	float h;

	Rect();
	Rect(float x, float y, float w, float h);
	~Rect();
	void SetPos(float x, float y);
	void SetPos(Vec2 pos);
	void SetSize(float w, float h);
	void SetSize(Vec2 size);
	void SetCenter(float x, float y);
	void SetCenter(Vec2 center);
	bool Contains(float a, float b);
	bool Contains(Vec2 p);
	Vec2 GetPos();
	Vec2 GetSize();
	Vec2 GetCenter();
};

#endif /* RECT_H_ */
