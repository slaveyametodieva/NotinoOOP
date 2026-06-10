#pragma once
#include "ICommand.h"
#include "BuyerCommandBase.h"

class CancelPurchaseCommand : public BuyerCommandBase
{
	public:
		CancelPurchaseCommand(Buyer* b);
		void execute() override;
};

