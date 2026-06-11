#include "CreateFragranceCommand.h"
#include <iostream>
CreateFragranceCommand::CreateFragranceCommand(Admin* a, std::vector<Fragrance>& cat): AdminCommandBase(a), catalog(cat)
{
}

void CreateFragranceCommand::execute()
{
	std::string name;
	int brandInt, familyInt;
	double price;

	std::cin >> name >> brandInt >> price >> familyInt;

	Brand b = static_cast<Brand>(brandInt);
	FregranceFamily f = static_cast<FregranceFamily>(familyInt);
	admin->createFragrance(name, b, price, f, catalog);
}

