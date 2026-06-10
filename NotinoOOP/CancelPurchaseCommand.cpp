#include "CancelPurchaseCommand.h"
#include <iostream>
CancelPurchaseCommand::CancelPurchaseCommand(Buyer* b): BuyerCommandBase(b)
{
}

void CancelPurchaseCommand::execute()
{
	unsigned int pID;
	std::cin >> pID;

	buyer->cancelPurchase(pID);
}
