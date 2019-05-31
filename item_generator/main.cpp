#include "itemGenerator.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
int main()
{
	std::string generated = itemGenerator::generate_item();
	std::cout << generated << std::endl;
	generated = itemGenerator::generate_item();
	std::cout << generated << std::endl;
	generated = itemGenerator::generate_item();
	std::cout << generated << std::endl;
	generated = itemGenerator::generate_item();
	std::ifstream inFile;
	std::unordered_set<std::string> words;
	std::string line;

	inFile.open("C:\\Users\\admin\\Desktop\\adjectives.txt");
	if (!inFile) {
		std::cerr << "Unable to open file";
		exit(1);   // call system to stop
	}
	while (getline(inFile, line)) {
		std::cout << line << std::endl;
	}
	inFile.close();
}