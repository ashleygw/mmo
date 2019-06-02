#include "itemGenerator.h"
unsigned itemGenerator::items_generated = 0;
std::unordered_set<char> itemGenerator::consonants = {};
std::unordered_set<std::string> itemGenerator::adjectives = {};

template <typename T>
void print_iterator(T& iter) {
	for (const auto& elem : iter) {
		std::cout << elem << std::endl;
	}
}

std::string itemGenerator::generate_item()
{
	itemGenerator::items_generated++;
	return std::string("eek" + std::to_string(itemGenerator::items_generated));
}

bool itemGenerator::is_unique_word(const std::unordered_set<std::string>& dictionary, const std::string& word)
{
	return dictionary.count(word) != 0;
}

std::unordered_set<std::string> itemGenerator::Add_er_est(const std::string & word)
{
	std::unordered_set<std::string> ret;
	ret.insert(word);
	if (word.size() > 2) // Make sure we can do the index backwards cvc
	{
		char lastLetter = word[word.size() - 1];
		char secondToLastLetter = word[word.size() - 2];
		char thirdToLastLetter = word[word.size() - 3];
		if (consonants.find(lastLetter) != consonants.end() && // c + v + c ending
			consonants.find(secondToLastLetter) == consonants.end() &&
			consonants.find(thirdToLastLetter) != consonants.end())
		{
			ret.insert(word + lastLetter + "er");
			ret.insert(word + lastLetter + "est");
		}
		else if (lastLetter == 'y' && consonants.find(secondToLastLetter) != consonants.end()) // c + y
		{
			std::string temp = word.substr(0, word.size() - 1);
			temp = temp + 'i';
			ret.insert(temp + "er");
			ret.insert(temp + "est");
		}
		else if (lastLetter == 'e' && consonants.find(secondToLastLetter) != consonants.end()) //c + e
		{
			ret.insert(word + "r");
			ret.insert(word + "st");
		}
	}
	print_iterator(ret);
	return ret;
}

void itemGenerator::setup_datastructures()
{
	itemGenerator::setup_consonants();
	itemGenerator::load_adjectives();
}

void itemGenerator::setup_consonants() {
	const char consonant_to_load[20] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z'};
	for (int i = 0; i < 20; i++)
		consonants.insert(consonant_to_load[i]);
}

void itemGenerator::load_adjectives() {
	std::ifstream inFile;
	std::unordered_set<std::string> words;
	std::string line;

	inFile.open("C:\\Users\\admin\\Desktop\\adjectives.txt");
	if (!inFile) {
		std::cerr << "Unable to open adjectives file.";
		exit(1);
	}
	std::string word;
	std::unordered_set<std::string> validWords;
	while (getline(inFile, line)) {
		if (line.find("1") != -1) {
			word = line.substr(0, line.find(" "));
			validWords = itemGenerator::Add_er_est(word);

		}
		for (const auto& elem : validWords) {
			adjectives.insert(elem);
		}
	}
	inFile.close();
}