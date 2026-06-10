#include "AddQuantityCommand.h"
#include <iostream>
#include <print>
AddQuantityCommand::AddQuantityCommand(Admin* a, std::vector<Fragrance>& cat): AdminCommandBase(a), catalog(cat)
{
}

void AddQuantityCommand::execute()
{
	std::string fName;
	unsigned int qty;

	std::cin >> fName >> qty;
	admin->addQuantity(fName, qty, catalog);
}
