#include "Fragrance.h"
#include <stdexcept>
#include <algorithm>
#include <print>
unsigned int Fragrance::fregranceID = 1;

Fragrance::Fragrance(const std::string& inpName, double inpPrice, FregranceFamily inpFFamily, 
					unsigned int inpQuntity, Brand inpBrand, std::vector<Review> inpCurrReviews)
					: name(inpName), price(inpPrice), currFFamily(std::move(inpFFamily)), quantity(inpQuntity),
					 perfumeBrand(std::move(inpBrand)), currReviews(std::move(inpCurrReviews))
{
	if (price < MIN_PRICE)
	{
		throw std::invalid_argument("The inputed price is below the minimum price for a perfume");
	}

	currFregranceID = fregranceID;
	fregranceID++;
}

double Fragrance::getRating() const
{
	if (currReviews.size() == 0)
	{
		return 0;
	}

	double sumReviews = 0;
	for (const auto& currReview : currReviews)
	{
		sumReviews += currReview.getRating();
	}

	return sumReviews / currReviews.size();
	
}

unsigned int Fragrance::getFregranceID() const
{
	return currFregranceID;
}

const std::string& Fragrance::getPName() const
{
	return name;
}

double Fragrance::getPPrice() const
{
	return price;
}

const FregranceFamily Fragrance::getFFamily() const
{
	return currFFamily;
}

unsigned int Fragrance::getQuantity() const
{
	return quantity;
}

const Brand Fragrance::getBrand() const
{
	return perfumeBrand;
}

void Fragrance::addQuantity(unsigned int inpQuantity)
{
	quantity += inpQuantity;
}

void Fragrance::removeQuantity(unsigned int inpQuantity)
{
	if (inpQuantity > quantity)
	{
		throw std::logic_error("Can not be removed more than the quantity of the perfume");
	}

	quantity -= inpQuantity;
}

void Fragrance::addReview(const Review& addingReview)
{
	currReviews.push_back(addingReview);
}

void Fragrance::removeReviewByID(unsigned int RIDToBeRemoved)
{
	if (RIDToBeRemoved >= currReviews.size())
	{
		throw std::out_of_range("The inputed ID is more than the current count of reviews for the perfume");
	}

	auto findIt = std::erase_if(currReviews, [RIDToBeRemoved](const Review& currReview)
		{return currReview.getReviewID() == RIDToBeRemoved; });

	if (findIt == currReviews.size())
	{
		throw std::logic_error("The inputed review was not found");
	}
	else
	{
		std::println("The review has successfully been removed from the list");
	}
}

void Fragrance::printFregrance() const
{
	std::println("FregranceID: {}, name: {}, price: {} euros, fregrance family - {}, quantity: {}, brand -{} "
				, currFregranceID, name, price, currFFamily, quantity, perfumeBrand);
	
	std::println("Current reviews for the perfume: ");
	for (const auto& currR : currReviews)
	{
		currR.printReview();
	}
}
