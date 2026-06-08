#include "Fragrance.h"
#include <stdexcept>
#include <algorithm>
#include <print>
unsigned int Fragrance::fregranceID = 1;

Fragrance::Fragrance(const std::string& inpName, double inpPrice, FregranceFamily inpFFamily, 
					unsigned int inpQuntity, Brand inpBrand, std::vector<Review> inpCurrReviews)
					: name(inpName), price(inpPrice), currFFamily(inpFFamily), quantity(inpQuntity),
					 perfumeBrand(inpBrand), currReviews(std::move(inpCurrReviews))
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

 Brand Fragrance::getBrand() const
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

		std::erase_if(currReviews, [RIDToBeRemoved](const Review& currReview)
		{return currReview.getReviewID() == RIDToBeRemoved; });

	
}

void Fragrance::printFregrance() const
{
	std::println("FregranceID: {}, name: {}, price: {} euros, fregrance family - {}, quantity: {}, brand -{} "
				, currFregranceID, name, price, getFFamilyAsString(currFFamily), quantity, getBrandAsString(perfumeBrand));
	
	std::println("Current reviews for the perfume: ");
	for (const auto& currR : currReviews)
	{
		currR.printReview();
	}
}

const std::string Fragrance::getFFamilyAsString(const FregranceFamily& currFF) const
{
	switch (currFF)
	{
	case FregranceFamily::FRUITY :
		return	"Fruity";
	case FregranceFamily::FLORAL:
		return "Floral";
	case FregranceFamily::AROMATIC:
		return "Aromatic";
	case FregranceFamily::GREEN:
		return "Green";
	case FregranceFamily::WOODS :
		return "Woods";
	case FregranceFamily::CITRUS:
		return "Citrus";
	case FregranceFamily::AMBER:
		return "Amber";
	case FregranceFamily::WOODY_AMBER:
		return "Woody amber";
	case FregranceFamily::SOFT_AMBER:
		return "Soft amber";
	default: return "Not found";
	}
}

const std::string Fragrance::getBrandAsString(const Brand& currB) const
{
	switch (currB)
	{
	case Brand::AlHaramain:
		return "AlHaramain";
	case Brand::BillieEilish:
		return "BillieEilish";
	case Brand::Chloe:
		return "Chloe";
	case Brand::Creed:
		return "Creed";
	case Brand::Dior:
		return "Dior";
	case Brand::Zadig_Voltaire:
		return "Zadig_Voltaire";
	case Brand::Mugler:
		return "Mugler";
	case Brand::Valentino:
		return "Valentino";
	case Brand::Xerjoff:
		return "Xerjoff";
	case Brand::YvesSauintLaurent:
		return "YvesSauintLaurent";
	case Brand::JeanPaulGultier:
		return "JeanPaulGultier";
	default :
		return "The brand is not found";
	}
}

std::string Fragrance::getRAuthorName(unsigned int reviewID) const
{
	auto foundIt = std::find_if(currReviews.begin(), currReviews.end(), [reviewID](const Review& currR)
		{return currR.getReviewID() == reviewID; });

	if (foundIt != currReviews.end())
	{
		return foundIt->getAuthorName();
	}

	return "";
}
