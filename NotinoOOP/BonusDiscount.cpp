#include "BonusDiscount.h"
#include <stdexcept>
BonusDiscount::BonusDiscount(double inpDisPercantage, double inpBonus) : Discount(inpDisPercantage)
{
	if (inpBonus < minBonus)
	{
		throw std::invalid_argument("The bonus can not be a negative number");
	}
	bonus = inpBonus;
}

double BonusDiscount::applyDiscount(double initPrice, Brand brand) const
{
	double priceAfterPercent = initPrice - (initPrice * (disPercantage / 100.0));

	double finalPrice = priceAfterPercent - bonus;
	if (finalPrice < 0)
	{
		return 0;
	}
	return finalPrice;
}
