#include "BrandDiscount.h"

BrandDiscount::BrandDiscount(double inpDisPercantage, Brand inpTargetBrand) : 
	Discount(inpDisPercantage), targetBrand(inpTargetBrand)
{
}

double BrandDiscount::applyDiscount(double initPrice, Brand brand) const
{

	if (targetBrand == brand)
	{
		double priceAfterPercent = initPrice - (initPrice * (disPercantage / 100.0));
		return priceAfterPercent;
	}
	return initPrice;
}
