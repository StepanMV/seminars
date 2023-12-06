#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <chrono>

namespace fs = std::filesystem;

void seekLineStart(std::ifstream& file) {
    for(char ch = file.peek(); ch != '\n'; file.seekg(-2, std::ios_base::cur), ch = file.peek());
    file.get();
}

std::pair<std::string, size_t> getFirstHash(std::ifstream& file) {
    file.seekg(0, std::ios_base::beg);
    std::string hash;
    std::getline(file, hash, '\t');
    return {hash, 0};
}

std::pair<std::string, size_t> getLastHash(std::ifstream& file) {
    file.seekg(-3, std::ios_base::end);
    seekLineStart(file);
    std::string hash;
    std::getline(file, hash, '\t');
    file.seekg(0, std::ios_base::end);
    return {hash, file.tellg()};
}

std::string binarySearch(std::string hash, std::ifstream& file, size_t streamSize) {
    streamSize /= 2;
    size_t mid = streamSize;
    while (streamSize) {
        file.seekg(mid);
        std::string midHash;
        std::getline(file, midHash, '\n');
        std::getline(file, midHash, '\t');
        if (midHash == hash) {
            std::string decoded;
            std::getline(file, decoded, '\n');
            return decoded;
        } else if (midHash > hash) {
            streamSize /= 2;
            mid -= streamSize;
        } else {
            streamSize /= 2;
            mid += streamSize;
        }
    }
    return "Not found";
}

int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <hash>\n";
        return 1;
    }
    std::string hash = "\"" + std::string(argv[1]) + "\"";
    fs::path dir = std::filesystem::current_path() / "data";
    for (auto& entry : fs::recursive_directory_iterator(dir)) {
        std::ifstream file(entry.path());
        auto [firshHash, firstPos]= getFirstHash(file);
        auto [lashHash, lastPos] = getLastHash(file);
        file.seekg(0);
        if(firshHash <= hash && hash <= lashHash) {
            std::cout << binarySearch(hash, file, lastPos) << std::endl;
            break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Program took " << diff.count() << " microseconds to run\n";
    return 0;
}