#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage:" << argv[0] << "<input_file> <output_file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cout << "Failed to open input file." << std::endl;
        return 1;
    }

    std::ofstream outputFile(argv[2]);
    if (!outputFile) {
        std::cout << "Failed to open output file." << std::endl;
        return 1;
    }

    std::vector<int> sequence;
    int num;
    while (inputFile >> num) {
        sequence.push_back(num);
    }
    
    auto last = std::unique(sequence.begin(), sequence.end());
    sequence.erase(last, sequence.end());

    int count0 = std::count(sequence.begin(), sequence.end(), 0);
    int count1 = std::count(sequence.begin(), sequence.end(), 1);

    outputFile << count0 << " " << count1 << std::endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
