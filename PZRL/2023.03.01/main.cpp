import <iostream>;
import Vector2;

std::ostream& operator<<(std::ostream& os, const Vector2& v2)
{
    os << "Vec2{" << v2.x << ", " << v2.y << "}\n";
    return os;
}

int main()
{
    Vector2 a(1, 2);
    Vector2 b(3, 4);
    Vector2 c = a + b;
    std::cout << c << std::endl;
    return 0;
}
