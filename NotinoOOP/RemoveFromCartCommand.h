#pragma once
#include "ICommand.h"
#include "Buyer.h"
#include "BuyerCommandBase.h"

class RemoveFromCartCommand : public BuyerCommandBase
{

	public:
		RemoveFromCartCommand(Buyer* b);
		void execute() override;
};

