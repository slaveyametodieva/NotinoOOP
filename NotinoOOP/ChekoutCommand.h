#pragma once
#include "ICommand.h"
#include "Buyer.h"
#include "BuyerCommandBase.h"

class ChekoutCommand : public BuyerCommandBase
{

	public:
		ChekoutCommand(Buyer* b);
		void execute() override;
};

