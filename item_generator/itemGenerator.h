#pragma once
#include <string>
#include <unordered_set>
class itemGenerator {
public:
	static std::string generate_item();
	static std::string tree_to_string();
	
	itemGenerator() = delete;
private:
	static unsigned items_generated;
	static std::unordered_set<std::string> adjectives;
	static std::unordered_set<std::string> weapons;
	static std::unordered_set<std::string> rings;
	static std::unordered_set<std::string> helms;
	static std::unordered_set<std::string> necklaces;
	static std::unordered_set<std::string> gloves;
	static std::unordered_set<std::string> boots;
	static std::unordered_set<std::string> leg_armor;
	static std::unordered_set<std::string> chest_armor;
};