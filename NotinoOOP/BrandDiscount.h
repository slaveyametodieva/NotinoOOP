#pragma once
#include "Discount.h"
#include "Fragrance.h"
class BrandDiscount : public Discount
{
	private:
		Brand targetBrand;
	public:
		BrandDiscount(double inpDisPercantage, Brand inpTargetBrand);
		double applyDiscount(double initPrice, Brand brand)const override;
};

