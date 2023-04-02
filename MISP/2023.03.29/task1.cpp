#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
#include <map>

int main(int argc, char* argv[])
{
    if (argc != 2) return -1;
    std::map<std::string, std::pair<int, double>> _map;
    std::ifstream data(argv[1]);
    if (!data.is_open()) return -1;
    while (data)
    {
        std::string name;
        int number;
        double grade;
        data >> name;
        if (name.empty()) continue;
        data >> number;
        data >> grade;
        _map.insert({name, std::make_pair(number, grade)});
    }

    for (auto it = _map.begin(); it != _map.end();)
    {
        if (it->second.second < 3) it = _map.erase(it);
        else ++it;
    }

    for (auto& it : _map)
    {
        std::cout << it.first << ": {" << it.second.first << " " << it.second.second << "}\n";
    }
    return 0;
}
