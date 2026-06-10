#pragma once
#include "Buyer.h"
#include "ICommand.h"
#include "Fragrance.h"
#include "BuyerCommandBase.h"
#include <vector>
class AddToCartCommand : public BuyerCommandBase
{
	private:
		std::vector<Fragrance>& catalog;

	public:
		AddToCartCommand(Buyer* b, std::vector<Fragrance>& cat);
		void execute() override;
};

