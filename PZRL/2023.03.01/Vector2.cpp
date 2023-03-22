export module Vector2;

import <iostream>;

export struct Vector2
{   
    int x = 0;
    int y = 0;

    Vector2() = default;
    ~Vector2() = default;

    Vector2(int valX, int valY)
    {
        x = valX;
        y = valY;
    }

    Vector2 operator+(const Vector2& other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }
};
