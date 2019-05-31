#include "itemGenerator.h"
unsigned itemGenerator::items_generated = 0;
std::string itemGenerator::generate_item()
{
	itemGenerator::items_generated++;
	return std::string("kek" + std::to_string(itemGenerator::items_generated));
}

