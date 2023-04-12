import RGBA;
import <iostream>;

int main()
{
    RGBA color(200, 0, 200, 128);
    RGBA color2(10, 10, 10, 10);
    color.print();
    RGBA newColor = color.sum(color2);
    newColor.print();
    newColor.print(E_INT);
    return 0;
}
