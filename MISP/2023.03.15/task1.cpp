#include <iostream>
#include <sstream>

int main()
{
    std::string str;
    std::cin >> str;
    std::istringstream ss(str);
    std::string tok;
    size_t i = 0;
    while (std::getline(ss, tok, ';'))
    {
        tok = tok.substr(tok.rfind('/') + 1);
        std::cout << i++ << ": " << tok << std::endl;
    }
    return 0;
}
