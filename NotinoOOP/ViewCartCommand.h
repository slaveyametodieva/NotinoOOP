#pragma once
#include "Buyer.h"
#include "BuyerCommandBase.h"

class ViewCartCommand : public BuyerCommandBase

{

	public:
		ViewCartCommand(Buyer* b);
		void execute() override;
};

