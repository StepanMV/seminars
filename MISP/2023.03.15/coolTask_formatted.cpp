#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    
    
    if (argc < 2) return -1;
    std::ifstream inp(argv[1]);
    std::string filename(argv[1]);
    std::string ext(argv[1]);
    filename = filename.substr(0, filename.rfind("."));
    ext = ext.substr(ext.rfind("."));
    std::string outFilename = filename + "_formatted" + ext;
    if (std::ifstream(outFilename).is_open())
    {
        std::cout << "File already exists. Do you wish to proceed? [Y/N]\n";
        char answer;
        std::cin >> answer;
        if (answer != 'Y') return -1;
    }
    std::ofstream outp(outFilename);
    if (!inp.is_open() || !inp.is_open()) return -1;
while (inp)
    {
        std::string line;
        std::getline(inp, line, '\n');
        if (line.contains("
        {
            line = line.substr(0, line.find("
        }
        if (line.contains("
")) std::getline(inp, line, '\n');
            line = line.substr(line.find("*/") + 2);
        }
        outp << line << std::endl;
    }
    return 0;
}

