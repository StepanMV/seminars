#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

int unclosedBrackets(const string& inputString) {
    stack<pair<char, int>> bracketStack;
    unordered_map<char, char> closingBrackets = {{']', '['}, {'}', '{'}, {')', '('}};

    for (int i = 0; i < inputString.length(); i++) {
        char currentChar = inputString[i];
        if (currentChar == '[' || currentChar == '{' || currentChar == '(') {
            bracketStack.push({currentChar, i});
        } else if (currentChar == ']' || currentChar == '}' || currentChar == ')') {
            if (bracketStack.empty()) {
                return i;
            }
            char lastOpeningBracket = bracketStack.top().first;
            int lastOpeningBracketIndex = bracketStack.top().second;
            bracketStack.pop();
            if (lastOpeningBracket != closingBrackets[currentChar]) {
                return lastOpeningBracketIndex;
            }
        }
    }

    return bracketStack.empty() ? -1 : bracketStack.top().second;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input string>" << endl;
        return 1;
    }
    string input = argv[1];
    int result = unclosedBrackets(input);

    cout << (result == -1 ? "Success" : std::to_string(result)) << endl;

    return 0;
}
