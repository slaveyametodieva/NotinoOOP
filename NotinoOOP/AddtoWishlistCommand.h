#pragma once
#include "Buyer.h"
#include "ICommand.h"
#include "BuyerCommandBase.h"
#include "Fragrance.h"
#include "BuyerCommandBase.h"

class AddtoWishlistCommand : public BuyerCommandBase
{
	std::vector<Fragrance>& catalog;

	public:
		AddtoWishlistCommand(Buyer* b, std::vector<Fragrance>& cat);
		void execute() override;

};

