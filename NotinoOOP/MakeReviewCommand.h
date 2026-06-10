#pragma once
#include "ICommand.h"
#include <vector>
#include "BuyerCommandBase.h"

#include "Fragrance.h"
class MakeReviewCommand: public BuyerCommandBase
{
	private:
		std::vector<Fragrance>& catalog;
	public:
		MakeReviewCommand(Buyer* b, std::vector<Fragrance>& cat);
		void execute() override;
};

