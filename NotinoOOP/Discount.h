#pragma once
#include "Brand.h"
constexpr double minPercantage = 0;
constexpr double maxPercantage = 100;
class Discount
{
	private:
		static unsigned int ID;
		unsigned int currDID;

	protected:
		double disPercantage;

	public:
		Discount(double inpDisPercantage);
		virtual ~Discount() = default;
		virtual double applyDiscount(double initPrice, Brand brand)const = 0;
		
		unsigned int getCurrDID() const;

};

