#include "MakeReviewCommand.h"
#include <iostream>
#include <print>
MakeReviewCommand::MakeReviewCommand(Buyer* b, std::vector<Fragrance>& cat): BuyerCommandBase(b), catalog(cat)
{
}

void MakeReviewCommand::execute()
{
	std::string fName; double rating; std::string comment;
	std::cin >> fName >> rating;
	std::cin.ignore();
	std::getline(std::cin, comment);

	bool found = false;

	for (auto& perf : catalog) {
		if (perf.getPName() == fName) {
			Review newReview(buyer->getUsername(), perf.getPName(), rating, comment);
			perf.addReview(newReview);
			std::println("Review added successfully for '{}'!", fName);
			found = true; 
			break;
		}
	}
	if (!found) std::println("Error: Fragrance '{}' not found.", fName);
}

