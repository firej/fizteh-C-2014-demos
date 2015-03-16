#include <utility>
#define _USE_MATH_DEFINES
#include <math.h>

typedef std::pair<double, double> point;
typedef std::pair<point, point> segment;

class CircleException {

};

class Shape {
public:
	virtual double getSquare() = 0;
	virtual bool CheckShape(point) = 0;
	virtual bool CheckIn(point) = 0;
	virtual point Cross(segment) = 0;
};

class Circle : Shape {
public:
	point center;
	double radius;
	Circle(){}
    Circle(point pcenter, double pradius) : center(pcenter), radius(pradius) {}
	virtual double getSquare(){
		return M_PI * pow(radius, 2);
	};
	virtual bool CheckShape(point p){
		return abs(pow((p.first - center.first), 2) + pow((p.second - center.second), 2) - pow(radius, 2)) < DBL_EPSILON;
	};
	virtual bool CheckIn(point p){
		return pow((p.first - center.first), 2) + pow((p.second - center.second), 2) <= pow(radius, 2);
	};
	virtual point Cross(segment s){
		if (s.first.second == s.second.second )
			if (radius*radius - pow(s.first.second - center.second, 2) > 0) {
				point p;
				p.first = center.first - pow(s.first.second - center.second, 2) + radius*radius;
				p.second = s.first.second;
				return p;
			}
			else {
				if (pow(s.first.second - center.second, 2) - radius*radius == 0){
					point p;
					p.first = center.first;
					p.second = s.first.second;
					return p;
				}
				else throw CircleException();
			}
		else {
			double k = (s.first.first - s.second.first) / (s.first.second - s.second.second);
			double b = (s.second.first * s.first.second - s.first.first * s.second.second) / (s.first.second - s.second.second) - center.first;
			double D = pow(center.second + b*k, 2) - (1 + k * k)*(center.second * center.second + b * b - radius * radius);
			if (D > 0) {
				point p;
				p.second = (center.second + b*k + sqrt(D)) / (1 + k * k);
				p.first = (s.first.first*s.second.second - s.second.first*s.first.second - (s.first.first - s.second.first) * p.second) / (s.first.second - s.second.second);
				return p;
			}
			else {
				if (D == 0){
					point p;
					p.second = (center.second + b*k) / (1 + k * k);
					p.first = (s.first.first * s.second.second - s.second.first * s.first.second - (s.first.first - s.second.first) * p.second) / (s.first.second - s.second.second);
					return p;
				}
				else throw CircleException();
			}
		
		}

		// Уравнение окружности -
		// (x - x0)^2 + (y - y0)^2 = r^2
		// Уравнение прямой по отрезку
		// (x1 - x2)*y + (y1 - y2)*x - (x1y2 - x2y1) = 0

		// x = (-(x2y1 - x1y2) - (x1 - x2)*y) / (y1 - y2)
		// (y - y0)^2 + (((x2y1 - x1y2) - (x1 - x2)*y) / (y1 - y2) - x0)^2 = r^2

		// b = (s.second.first * s.first.second - s.first.first * s.second.second)/(s.first.second - s.second.second) - center.first
		/*
		k = (s.first.first - s.second.first) / (s.first.second - s.second.second)
		(y-center.second)^2 + (b - ky)^2 = r^2
		y^2 * (1 + k^2) - 2* (center.second + bk) * y + center.second^2 + b^2 - r^2 = 0
		D/4 = (center.second + bk)^2 - (1 + k^2)*(center.second^2 + b^2 - r^2)
		y = (center.second + bk ± D/4) / (1 + k^2)

		if (y1 == y2)
		y = y1
		D/4 = (y1 - y0)^2 - r^2
		x = x0 ± D/4




		*/



	//	return point(0,0);
	};
};