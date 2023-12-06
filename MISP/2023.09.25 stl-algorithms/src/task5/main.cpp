#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
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

    int N;
    inputFile >> N;

    std::vector<int> cards(N);
    for (int i = 0; i < N; i++) {
        inputFile >> cards[i];
    }

    //std::sort(cards.begin(), cards.end(), std::greater<int>());
    std::partial_sort(cards.begin(), cards.begin() + cards.size() / 2, cards.end(), std::greater<int>());

    int maxWinnings = std::accumulate(cards.begin(), cards.begin() + cards.size() / 2, 0);

    outputFile << maxWinnings << std::endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
