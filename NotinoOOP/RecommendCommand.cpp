#include "RecommendCommand.h"

RecommendCommand::RecommendCommand(Buyer* b,  std::vector<Fragrance>& cat): BuyerCommandBase(b), catalog(cat)
{
}

void RecommendCommand::execute()
{
	buyer->recommend(catalog);
}
