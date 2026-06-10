#pragma once
#include "ICommand.h"
class BuyerCommandBase : public ICommand
{
	protected:
		Buyer* buyer;

	public:
		BuyerCommandBase(Buyer* b);
};

