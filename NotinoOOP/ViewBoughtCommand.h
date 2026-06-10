#pragma once
#include "ICommand.h"
#include "BuyerCommandBase.h"

class ViewBoughtCommand : public BuyerCommandBase
{
	public:
		ViewBoughtCommand(Buyer* b);
		void execute() override;
};

