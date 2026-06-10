#pragma once
#include "BuyerCommandBase.h"

#include "ICommand.h"
class ViewPurchasesCommand : public BuyerCommandBase
{
	public:
		ViewPurchasesCommand(Buyer* b);
		void execute() override;
};

