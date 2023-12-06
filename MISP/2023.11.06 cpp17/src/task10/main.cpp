#include <iostream>
#include <regex>
#include <filesystem>

namespace fs = std::filesystem;

std::string strReplace(std::string str, std::string findStr, std::string replaceStr) {
    size_t index = 0;
    while (true) {
        index = str.find(findStr, index);
        if (index == std::string::npos) break;
        str.replace(index, findStr.size(), replaceStr);
        index += findStr.size();
    }
    return str;
}

int main(int argc, char* argv[]) {
    if (argc != 4 && argc != 5) {
        std::cout << "Usage: " << argv[0] << " <directory> [-r] <find> <replace>" << std::endl;
        return 1;
    }
    fs::path dir = fs::current_path() / argv[1];
    if (!fs::exists(dir)) throw std::runtime_error("Directory does not exist");
    if (!fs::is_directory(dir)) throw std::runtime_error(dir.string() + " is not a directory");
    bool useRegex = argc == 5 && argv[2] == "-r";
    std::string findStr = argc == 4 ? argv[2] : argv[3];
    std::string replaceStr = argc == 4 ? argv[3] : argv[4];

    for (auto& entry : fs::recursive_directory_iterator(dir)) {
        std::string filename;
        if (useRegex)
            filename = std::regex_replace(entry.path().filename().string(), std::regex(findStr), replaceStr);
        else
            filename = strReplace(entry.path().filename().string(), findStr, replaceStr);
        fs::rename(entry, entry.path().parent_path() / filename);
    }
    return 0;
}