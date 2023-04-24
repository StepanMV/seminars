import RGBA;
import <iostream>;
import <vector>;

int main()
{
    const size_t len = 5;
    srand(time(NULL));
    std::vector<RGB> colors1;
    std::vector<RGBA> colors2;
    std::vector<RGB*> colors;
    for (size_t i = 0; i < len; ++i)
    {
        RGB color(rand() % 256, rand() % 256, rand() % 256);
        colors1.push_back(color);
        colors.push_back(&color);
    }

    for (size_t i = 0; i < len; ++i)
    {
        RGBA color(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
        colors2.push_back(color);
        colors.push_back(&color);
    
    }

    for (size_t i = 0; i < 2 * len; ++i)
    {
        colors[i]->print(E_HEX);
    }

    /*for (size_t i = 0; i < len; ++i)
    {
        colors2[i].print(E_HEX);
    }*/

    RGBA newColor = colors2[0].sum(colors2[len - 1]);
    newColor.print(E_HEX);
    newColor.print(E_INT);
    return 0;
}
