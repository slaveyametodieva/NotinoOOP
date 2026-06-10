#pragma once
#include "BuyerCommandBase.h"
#include "Buyer.h"
#include <string>
class AddToBalanceCommand : public BuyerCommandBase
{

	public:
		AddToBalanceCommand(Buyer* b);
		void execute() override;

};

