#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

map<string, int> dictionary;

map<string, int> loadDictionary(string filename)
{
	map<string, int> dictionary;
	ifstream file(filename);
	string word;
	int weight;
	while (file >> word >> weight)
	{
		word = word.substr(0, word.length() - 1);
		dictionary[word] = weight;
	}
	return dictionary;
}

vector<vector<string>> getWords(string input)
{
	std::istringstream iss(input);
	vector<vector<string>> permutations;
	size_t pos = 0;
	string in_word;
	while (iss >> in_word)
	{
		permutations.push_back(vector<string>());
		bool found = false;
		for (auto [word, weight] : dictionary)
		{
			if (word.length() == in_word.length() && is_permutation(word.begin(), word.end(), in_word.begin()))
			{
				permutations[pos].push_back(word);
				found = true;
			}
		}
		if (!found)
		{
			std::cout << "No word found for " << in_word << std::endl;
			exit(0);
		}
		pos++;
	}
	return permutations;
}

void generateSentences(vector<vector<string>>& sentences, vector<string>& sentence, vector<vector<string>>& words, int index) {
    if (index == words.size()) {
        sentences.push_back(sentence);
        return;
    }

    for (auto& word : words[index]) {
        sentence.push_back(word);
        generateSentences(sentences, sentence, words, index + 1);
        sentence.pop_back();
    }
}


void solve(string input)
{
	auto words = getWords(input);
	vector<vector<string>> sentences;
	vector<string> sntc;
	generateSentences(sentences, sntc, words, 0);
	
	auto weightSort = [](vector<string>& a, vector<string>& b) {
		int weightA = 0;
		int weightB = 0;
		for (auto& word : a) weightA += dictionary[word];
		for (auto& word : b) weightB += dictionary[word];
		return weightA > weightB;
	};

	size_t count = 1;
	sort(sentences.begin(), sentences.end(), weightSort);
	for (auto& sentence : sentences) {
		int weight = 0;
		sort(sentence.begin(), sentence.end());
		for (auto& word : sentence) weight += dictionary[word];
		do {
			cout << count++ << ". ";
			for (auto& word : sentence) cout << word << " ";
			cout << " | weight=" << weight << endl;
		} while (next_permutation(sentence.begin(), sentence.end()));
		std::cout << std::endl;
	}
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "Usage: ./program sentenceFile dictionaryFile" << endl;
		return 1;
	}
	string sentence = argv[1];
	string dictionaryFilename = argv[2];
	dictionary = loadDictionary(dictionaryFilename);
	solve(sentence);
	return 0;
}