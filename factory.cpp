#include <iostream>
#include <cmath>

class Point
{
    double x_,y_;
public:
    Point(double x, double y) : x_(x), y_(y) {}

    friend std::ostream& operator << (std::ostream &out, const Point &p)
    {
        out << "x = " << p.x_;
        out << '\n';
        out << "y = " << p.y_;
        out << '\n';
    }
};

struct PointFactory
{
    static Point createPointCartesianCoordinate(double x, double y)
    {
        return {x, y};
    }

    static Point createPointPolarCoordinate(double r, double theta)
    {
        return {r * std::cos(theta), r * std::sin(theta)};
    }
};

int main()
{
    Point point1 = PointFactory::createPointPolarCoordinate(2.5, 1.2);
    Point point2 = PointFactory::createPointCartesianCoordinate(2.2, 3.4);
    std::cout << point1 << point2 << std::endl;
    return 0;
}
