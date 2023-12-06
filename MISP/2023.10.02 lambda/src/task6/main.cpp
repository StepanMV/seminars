#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage:" << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    // Open input file
    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cout << "Failed to open input file." << std::endl;
        return 1;
    }

    // Read input file
    int N, a, b;
    inputFile >> N >> a >> b;

    std::vector<int> sequence;
    int num;
    while (inputFile >> num) {
        sequence.push_back(num);
    }

    // Print input data
    std::copy(sequence.begin(), sequence.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // Remove elements outside of [a, b]
    auto range = std::remove_if(sequence.begin(), sequence.end(), [a, b](int x) {return x < a || x > b;});
    sequence.erase(range, sequence.end());

    // Print the result
    std::copy(sequence.begin(), sequence.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // Remove first even after max
    auto maxElement = std::max_element(sequence.begin(), sequence.end());
    auto findEven = std::find_if(maxElement + 1, sequence.end(), [](int x) {return x % 2 == 0;});
    int even = *findEven;
    sequence.erase(findEven);

    // Print the result
    std::copy(sequence.begin(), sequence.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    // Print deleted even
    std::cout << std::distance(sequence.begin(), findEven) << " " << even << std::endl;

    // Print the amount of negative and positive numbers
    int countPos = std::count_if(sequence.begin(), sequence.end(), [](int x) {return x > 0;});
    int countNeg = std::count_if(sequence.begin(), sequence.end(), [](int x) {return x < 0;});
    std::cout << countPos << " " << countNeg << std::endl;

    inputFile.close();

    return 0;
}
