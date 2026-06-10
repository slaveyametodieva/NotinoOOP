#include "ViewPurchasesCommand.h"

ViewPurchasesCommand::ViewPurchasesCommand(Buyer* b): BuyerCommandBase(b)
{
}

void ViewPurchasesCommand::execute()
{
	buyer->viewBought();
}
