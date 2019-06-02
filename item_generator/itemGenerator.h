#pragma once
#include <string>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

class itemGenerator {
public:
	static std::string generate_item();
	static std::string tree_to_string();
	static bool is_unique_word(const std::unordered_set<std::string>&, const std::string&);
	static std::unordered_set<std::string> Add_er_est(const std::string&);
	static void setup_datastructures();
	
	itemGenerator() = delete;
private:
	static unsigned items_generated;
	static std::unordered_set<char> consonants;
	static void setup_consonants();
	static void load_adjectives();
	static std::unordered_set<std::string> adjectives;
	static std::unordered_set<std::string> weapons;
	static std::unordered_set<std::string> rings;
	static std::unordered_set<std::string> helms;
	static std::unordered_set<std::string> necklaces;
	static std::unordered_set<std::string> gloves;
	static std::unordered_set<std::string> boots;
	static std::unordered_set<std::string> leg_armor;
	static std::unordered_set<std::string> chest_armor;
	static std::unordered_set<std::string> spells;
};