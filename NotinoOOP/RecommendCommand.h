#pragma once
#include "Fragrance.h"
#include "ICommand.h"
#include "Buyer.h"
#include <vector>
#include "BuyerCommandBase.h"

class RecommendCommand : public BuyerCommandBase
{
	private:
		std::vector<Fragrance>& catalog;

	public:
		RecommendCommand(Buyer* b,  std::vector<Fragrance>& cat);
		void execute() override;

};

