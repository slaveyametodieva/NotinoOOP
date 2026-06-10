#include "ViewCartCommand.h"

ViewCartCommand::ViewCartCommand(Buyer* b): BuyerCommandBase(b)
{
}

void ViewCartCommand::execute()
{
	buyer->viewCart();
}
