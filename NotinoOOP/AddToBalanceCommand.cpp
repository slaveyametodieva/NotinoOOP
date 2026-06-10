#include "AddToBalanceCommand.h"
#include <iostream>
#include <stdexcept>
#include <print>
AddToBalanceCommand::AddToBalanceCommand(Buyer* b): BuyerCommandBase(b)
{
}

void AddToBalanceCommand::execute()
{
	double amount;
	std::cin >> amount;
	if (amount < 0)
	{
		throw std::invalid_argument("The added amount can not be a negative number");
	}

	buyer->addToBalance(amount);
	std::println("Successfully added {} to your balance!", amount);
}
