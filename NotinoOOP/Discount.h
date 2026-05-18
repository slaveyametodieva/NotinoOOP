#pragma once

constexpr int minPercantage = 0;
class Discount
{
	private:
		double percantage;
		static unsigned int ID;
		unsigned int currDID;

	public:
		Discount(double inpPercantage);
		virtual ~Discount() = default;
		virtual void applyDiscount() = 0;
		
		double getPercantage() const;
		unsigned int getCurrDID() const;

};

