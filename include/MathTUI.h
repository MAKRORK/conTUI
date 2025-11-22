#pragma once

namespace ctui
{
	struct vec2
	{
		int x;
		int y;
		vec2() : x(0), y(0) {}
		vec2(int _x, int _y) : x(_x), y(_y) {}
		vec2(int _p) : x(_p), y(_p) {}
		vec2 operator+(const vec2 &b) const { return vec2(x + b.x, y + b.y); }
		vec2 &operator+=(const vec2 &b)
		{
			x += b.x;
			y += b.y;
			return *this;
		}
		vec2 operator-(const vec2 &b) const { return vec2(x - b.x, y - b.y); }
		vec2 operator+(int b) const { return vec2(x + b, y + b); }
		vec2 operator-(int b) const { return vec2(x - b, y - b); }
		vec2 operator*(int b) const { return vec2(x * b, y * b); }
		vec2 operator/(int b) const { return vec2(x / b, y / b); }
		vec2 operator-() const { return vec2(-x, -y); }
		bool inRect(vec2 _p, vec2 _s);
	};
	int ctmin(int a, int b);
	int ctmax(int a, int b);
	double pov(double a, int p);
}
