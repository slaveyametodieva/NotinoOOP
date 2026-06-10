#include "ChekoutCommand.h"

ChekoutCommand::ChekoutCommand(Buyer* b): BuyerCommandBase(b)
{
}

void ChekoutCommand::execute()
{
	buyer->checkout();
}
