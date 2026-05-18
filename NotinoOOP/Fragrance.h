#pragma once
#include "Review.h"
#include "FregranceFamily.h"
#include "Brand.h"
#include <vector>

constexpr double MIN_PRICE = 40;
class Fragrance
{
private:
	static unsigned int fregranceID;
	unsigned int currFregranceID;
	std::string name;
	double price;
	FregranceFamily currFFamily;
	unsigned int quantity;
	Brand perfumeBrand;
	std::vector<Review> currReviews;

public:
	Fragrance(const std::string& inpName, double inpPrice, FregranceFamily inpFFamily,
		unsigned int inpQuntity, Brand inpBrand, std::vector<Review> inpCurrReviews);

	double getRating() const;
	unsigned int getFregranceID() const;
	const std::string& getPName() const;
	double getPPrice() const;
	const FregranceFamily getFFamily() const;
	unsigned int getQuantity() const;
	const Brand getBrand() const;

	void addQuantity(unsigned int inpQuantity);
	void removeQuantity(unsigned int inpQuantity);
	void addReview(const Review& addingReview);
	void removeReviewByID(unsigned int RIDToBeRemoved);

	void printFregrance() const;
	const std::string getFFamilyAsString(const FregranceFamily& currFF) const;
	const std::string getBrandAsString(const Brand& currB) const;
};

