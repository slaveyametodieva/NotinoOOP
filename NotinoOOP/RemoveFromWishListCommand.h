#pragma once
#include "Buyer.h"
#include "ICommand.h"
#include "BuyerCommandBase.h"
class RemoveFromWishListCommand : public BuyerCommandBase
{

	public:
	RemoveFromWishListCommand(Buyer* b);
	void execute() override;
};

