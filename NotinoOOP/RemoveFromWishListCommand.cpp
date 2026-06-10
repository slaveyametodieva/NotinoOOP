#include "RemoveFromWishListCommand.h"
#include <iostream>
#include <print>
RemoveFromWishListCommand::RemoveFromWishListCommand(Buyer* b): BuyerCommandBase(b)
{
}
void RemoveFromWishListCommand::execute()
{
	std::string fName;
	std::cin >> fName;

	buyer->removeFromWishList(fName);
	std::println("If '{}' was in your wishlist, it has been removed.", fName);
}
