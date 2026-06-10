#include "ViewBoughtCommand.h"

ViewBoughtCommand::ViewBoughtCommand(Buyer* b): BuyerCommandBase(b)
{
}

void ViewBoughtCommand::execute()
{
	buyer->viewBought();
}
