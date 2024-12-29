#include <iostream>
#include <string>
#include <cmath> // sqrt
#include <memory>

class Vec
{
private:
    int x;
    int y;

public:
    Vec(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}

    double length()
    {
        return std::sqrt(x * x + y * y);
    }

    bool isZero()
    {
        return length() == 0;
    }
};

int main()
{
    std::unique_ptr<Vec> vec2 = std::make_unique<Vec>(3, 4);
    std::cout << vec2->length() << std::endl;
}