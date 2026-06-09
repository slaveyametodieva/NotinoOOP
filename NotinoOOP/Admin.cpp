#include "Admin.h"
#include <print>
#include <algorithm>

Admin::Admin(const std::string& inpUsername, const std::string& inpPassword) : User(inpUsername, inpPassword)
{
}

void Admin::help() const
{
	std::println("--- Admin Menu Commands ---");
	std::println("block-user <username>");
	std::println("create-fragrance <name> <brand> <price> <fragranceFamily>");
	std::println("add-quantity <fragrance-name> <quantity>");
	std::println("deliver <purchase-id>");
	std::println("remove-review <fragrance-id> <review-id>");
	std::println("---------------------------");
}


void Admin::blockUser(const std::string& deletingUser, std::vector<std::unique_ptr<User>>& allUsers)
{
	auto removedUCount = std::erase_if(allUsers, [&deletingUser](const std::unique_ptr<User>& currU)
		{return currU->getUsername() == deletingUser; });

	if (removedUCount > 0)
	{
		std::println("User {} has been successfully blocked and their account was deleted", deletingUser);
		return;
	}
	else
	{
		std::println("User {} was not found", deletingUser);
	}
}

void Admin::createFragrance(const std::string& name, Brand brand, double price, FregranceFamily family,
							std::vector<Fragrance>& catalog)
{
	for (const auto& currF : catalog)
	{
		if (currF.getPName() == name)
		{
			std::println("A fragrance with the name {} already exists", name);
			return;
		}
	}

	std::vector<Review> emptyReviews;
	catalog.emplace_back(name, price, family, 0, brand, emptyReviews);
	std::println("Fragrance {} has been successfully added to the system", name);
}

void Admin::addQuantity(const std::string& fragranceName, unsigned int quantity, std::vector<Fragrance>& catalog)
{
	auto foundIt = std::find_if(catalog.begin(), catalog.end(), [&fragranceName](const Fragrance& currF)
		{return currF.getPName() == fragranceName; });

	if (foundIt != catalog.end())
	{
		foundIt->addQuantity(quantity);
		std::println("Successfully added {} to {}. The new quantity is {} ", quantity, fragranceName,
					foundIt->getQuantity());
		return;
	}

	std::println("Fragrance {} was not found", fragranceName);
}

void Admin::deliver(unsigned int purchaseID, std::vector<std::unique_ptr<User>>& allUsers)
{
	for (auto& currU : allUsers)
	{
		Buyer* buyerPtr = dynamic_cast<Buyer*>(currU.get());
		if (buyerPtr)
		{
			if (buyerPtr->deliverPurchase(purchaseID))
			{
				std::println("Order ID {} has been successfully changed to delivered", purchaseID);
				return;
			}
		}
	}
	std::println("Purchase with ID {} was not found or it is not in pending status", purchaseID);
}

void Admin::removeReview(unsigned int fregranceID, unsigned int reviewID, std::vector<Fragrance>& catalog, 
						std::vector<std::unique_ptr<User>>& allUsers)
{
	std::string authorName;

	for (auto& freg : catalog)
	{
		if (freg.getFregranceID() == fregranceID)
		{
			authorName = freg.getRAuthorName(reviewID);

			if (authorName.empty())
			{
				std::println("Review with ID {} was not found for this fregrance", reviewID);
				return;
			}

			freg.removeReviewByID(reviewID);
			std::println("Review by {} was successfully removed", authorName);
			break;
		}
	}

	if (authorName.empty())
	{
		std::println("Fregrance or review not found");
		return;
	}

	for (auto& currU : allUsers)
	{
		if (currU->getUsername() == authorName)
		{
			currU->incerementRemovedReviews();
			std::println("User {} now has {} removed reviews", authorName, currU->getRemovedReviewsCount());

			if (currU->getRemovedReviewsCount() >= 7)
			{
				std::println("User {} has already more or equal to 7 removed reviews", authorName);
				blockUser(authorName, allUsers);
			}
			return;
		}
	}
}