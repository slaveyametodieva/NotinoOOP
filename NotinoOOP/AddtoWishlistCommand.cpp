#include "AddtoWishlistCommand.h"
#include <print>
#include <iostream>
AddtoWishlistCommand::AddtoWishlistCommand(Buyer* b, std::vector<Fragrance>& cat): BuyerCommandBase(b), catalog(cat)
{
}

void AddtoWishlistCommand::execute()
{
	std::string fName;
	std::cin >> fName;

	bool found = false;
	for (const auto& perf : catalog) {
		if (perf.getPName() == fName) {
			buyer->addToWishList(perf);
			std::println("Fragrance '{}' was added to your wishlist.", fName);
			found = true;
			break;
		}
	}
	if (!found) std::println("Error: Fragrance '{}' does not exist.", fName);
}
