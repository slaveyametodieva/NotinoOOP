#pragma once
#include "Discount.h"

constexpr double minBonus = 0.0;

class BonusDiscount : public Discount
{
	private:
		double bonus;

	public:
		BonusDiscount(double inpDisPercantage, double inpBonus);
		double applyDiscount(double initPrice, Brand brand)const override;
};

