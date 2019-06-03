#include "itemGenerator.h"
#include <iostream>
#include <string>
int main()
{
	itemGenerator::setup_datastructures();
	std::string generated = itemGenerator::generate_item();
	std::cout << generated << std::endl;
	generated = itemGenerator::generate_item();
	std::cout << generated << std::endl;
}