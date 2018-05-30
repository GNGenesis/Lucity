#include "Rect.h"
#include "Vec2.h"

#include <algorithm>
#include <cmath>

class Collision {

	public:
		static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
			Vec2 A[] = {
				Vec2(a.x, a.y+a.h),
				Vec2(a.x+a.w, a.y+a.h),
				Vec2(a.x+a.w, a.y),
				Vec2(a.x, a.y)
			};
			Vec2 B[] = {
				Vec2(b.x, b.y+b.h),
				Vec2(b.x+b.w, b.y+b.h),
				Vec2(b.x+b.w, b.y),
				Vec2(b.x, b.y)
			};

			for(auto& v : A)
				v = Rotate(v-a.GetCenter(), angleOfA)+a.GetCenter();

			for(auto& v : B)
				v = Rotate(v-b.GetCenter(), angleOfB)+b.GetCenter();

			Vec2 axes[] = { Norm(A[0]-A[1]), Norm(A[1]-A[2]), Norm(B[0]-B[1]), Norm(B[1]-B[2]) };

			for(auto& axis : axes) {
				float P[4];

				for(int i = 0; i < 4; ++i)
					P[i] = Dot(A[i], axis);

				float minA = *std::min_element(P, P + 4);
				float maxA = *std::max_element(P, P + 4);

				for(int i = 0; i < 4; ++i)
					P[i] = Dot(B[i], axis);

				float minB = *std::min_element(P, P + 4);
				float maxB = *std::max_element(P, P + 4);

				if(maxA < minB || minA > maxB)
					return false;
			}

			return true;
		}

		static inline bool IsCollidingCircleCircle(Circle& a, Circle& b) {
			if (Distance(a.x, a.y, b.x, b.y) < (a.r + b.r)) {
				return true;
			}
			return false;
		}

		static inline bool IsCollidingCircleRect(Circle& a, Rect& b, float angleOfB) {
			int closestX, closestY;

			if (a.x < b.x) {
				closestX = b.x;
			}
			else if (a.x > b.x + b.w) {
				closestX = b.x + b.w; 
			}
			else { 
				closestX = a.x; 
			}

			if (a.y < b.y) {
				closestY = b.y;
			}
			else if (a.y > b.y + b.h) {
				closestY = b.y + b.h;
			}
			else {
				closestY = a.y;
			}
			if (Distance(a.x, a.y, closestX, closestY) < a.r) {
				return true;
			}
			return false;
		}

	private:
		static inline float Mag(const Vec2& p) {
			return std::sqrt(p.x*p.x + p.y*p.y);
		}

		static inline Vec2 Norm(const Vec2& p) {
			return p*(1.f / Mag(p));
		}

		static inline float Dot(const Vec2& a, const Vec2& b) {
			return a.x*b.x + a.y*b.y;
		}

		static inline Vec2 Rotate(const Vec2& p, float angle) {
			float cs = Vec2::Cos(angle), sn = Vec2::Sin(angle);
			return Vec2 (p.x*cs - p.y*sn, p.x*sn + p.y*cs);
		}
		static inline float Distance(float x1, float y1, float x2, float y2) {
			return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
		}
};
