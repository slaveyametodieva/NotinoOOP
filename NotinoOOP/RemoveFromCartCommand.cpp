#include "RemoveFromCartCommand.h"
#include <print>
#include <iostream>

RemoveFromCartCommand::RemoveFromCartCommand(Buyer* b) : BuyerCommandBase(b)
{
}

void RemoveFromCartCommand::execute()
{
	std::string fName; 
	std::cin >> fName;
	buyer->removeFromCart(fName);

	std::println("If '{}' was in your cart, it has been removed.", fName);
}
}
