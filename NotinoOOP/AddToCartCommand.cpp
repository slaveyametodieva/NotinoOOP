#include "AddToCartCommand.h"
#include <iostream>
#include <print>
AddToCartCommand::AddToCartCommand(Buyer* b, std::vector<Fragrance>& cat): BuyerCommandBase(b), catalog(cat)
{
}

void AddToCartCommand::execute()
{
	std::string fName;
	std::cin >> fName;
	
	bool found = false;
	for (const auto& pref : catalog)
	{
		if (pref.getPName() == fName)
		{
			buyer->addToCart(pref);
			std::println("Fragrance {} was added to your cart", fName);
			found = true;
			break;
		}
	}

	if(!found)
		std::println("Error: Fragrance '{}' does not exist in the store.", fName);
}
}
