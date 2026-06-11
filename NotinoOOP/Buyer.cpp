#include "Buyer.h"
#include <stdexcept>
#include <print>
#include <algorithm>
#include <iostream>
#include <random>

Buyer::Buyer(const std::string& inpUsername, const std::string& inpPassword, double initialBalance):
	User(inpUsername, inpPassword)
{
	if (initialBalance < minBalance)
	{
		throw std::invalid_argument("The balance can not be a negative number");
	}
	balance = initialBalance;
}

void Buyer::help() const
{
		std::println("--- Buyer Menu Commands ---");
		std::println("add-to-balance <amount>");
		std::println("view-cart");
		std::println("add-to-cart <fragrance-name>");
		std::println("checkout");
		std::println("recommend");
		std::println("add-to-wishlist <fragrance-name>");
		std::println("remove-from-wishlist <fragrance-name>");
		std::println("remove-from-cart <fragrance-name>");
		std::println("view-bought");
		std::println("view-purchases");
		std::println("cancel <purchase-id>");
		std::println("make-review <fragrance-name> <rating> <comment>");
		std::println("---------------------------");
}

void Buyer::addToBalance(double amount)
{
	if (amount < minBalance)
	{
		throw std::invalid_argument("The adding balance can not be a negative number");
	}
	balance += amount;
}

void Buyer::addToWishList(const Fragrance& inpFreg)
{
	wishlist.push_back(inpFreg);
}

void Buyer::removeFromWishList(const std::string& fregranceName)
{
	std::erase_if(wishlist, [&fregranceName](const Fragrance& f) {
		return f.getPName() == fregranceName;});
}

void Buyer::addToCart(const Fragrance& addingFreg)
{
	cart.push_back(addingFreg);
}

void Buyer::removeFromCart(const std::string& inpFregName)
{
	std::erase_if(cart, [&inpFregName](const Fragrance& f)
		{return f.getPName() == inpFregName; });
}

void Buyer::viewBought() const
{
	bool hasBought = false;

	std::println("Completed purchases");

	for (const auto& p : purchases)
	{
		if (p.status == PurchaseStatus::DELIVERED)
		{
			std::println("Order ID: {} | Total Price: {} euros", p.purchaseID, p.totalPrice);
			hasBought = true;
		}
	}

	if (!hasBought)
	{
		std::println("No successful purchases yet.");
	}
}

void Buyer::viewPurchase() const
{
	if (purchases.empty())
	{
		std::println("No order history");
		return;
	}
	else
	{
		std::println("All purchases history");

		for (const auto& p : purchases)
		{
			std::string statusStr;
			if (p.status == PurchaseStatus::PENDING) statusStr = "PENDING";
			else if (p.status == PurchaseStatus::DELIVERED) statusStr = "DELIVERED";
			else statusStr = "CANCELED";

			std::println("Order ID: {} | Status: {} | Total Price: {} euros", p.purchaseID, statusStr, p.totalPrice);
		}
	}
}

void Buyer::viewCart() const
{
	if (cart.empty())
	{
		std::println("The cart is empty!");
		return;
	}
	else
	{
		std::println("Current cart:");
		for (const auto& f : cart)
		{
			f.printFregrance();
			std::cout << '\n';
		}
	}
}

bool Buyer::deliverPurchase(unsigned int purchaseID)
{
	for (auto& currP : purchases)
	{
		if (currP.purchaseID == purchaseID)
		{
			if (currP.status == PurchaseStatus::PENDING)
			{
				currP.status = PurchaseStatus::DELIVERED;
				return true;
			}
		}
	}
	return false;
}

void Buyer::recommend(const std::vector<Fragrance>& perfumes) const
{
	if (wishlist.empty())
	{
		std::println("Your wishlist is empty. Add some perfumes so we can recommend you something");
		return;
	}

	FregranceFamily favouriteFamily = wishlist[0].getFFamily();
	int maxCount = 0;

	for (size_t i = 0; i < wishlist.size(); i++)
	{
		int currCount = 0;
		for (size_t j = 0; j < wishlist.size(); j++)
		{
			if (wishlist[i].getFFamily() == wishlist[j].getFFamily())
			{
				currCount++;
			}
		}

		if (currCount > maxCount)
		{
			maxCount = currCount;
			favouriteFamily = wishlist[i].getFFamily();
		}
	}

	std::vector<Fragrance> candidates;

	for (const auto& pref : perfumes)
	{
		if (pref.getFFamily() == favouriteFamily)
		{
			bool isInWishlist = false;
			for (const auto& currW : wishlist)
			{
				if (currW.getPName() == pref.getPName())
				{
					isInWishlist = true;
					break;
				}
			}

			if (!isInWishlist)
			{
				candidates.push_back(pref);
			}
		}
	}

	if (candidates.empty())
	{
		std::println("We could not find any new recommendations for your favourite fragrance family");
		return;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(candidates.begin(), candidates.end(), gen);

	std::println("We recommend for you: ");
	int count = 0;
	for (const auto& currC : candidates)
	{
		currC.printFregrance();
		count++;

		if (count == 4)
			break;
	}
	std::println("");
}

void Buyer::checkout()
{
	if (cart.empty())
	{
		std::println("The cart is currently empty");
		return;
	}

	double totalPrice = 0;
	for (const auto& currProduct : cart)
	{
		double currProdPrice = currProduct.getPPrice();
		totalPrice += currProdPrice;
	}

	double bestPrice = totalPrice;
	int bestDiscountIdx = -1;

	for (size_t i = 0; i < discounts.size(); i++)
	{
		double currTotalDiscount = 0;
		for (const auto& currProduct : cart)
		{
			currTotalDiscount += discounts[i]->applyDiscount(currProduct.getPPrice(), currProduct.getBrand());
		}

		if (currTotalDiscount < bestPrice)
		{
			bestPrice = currTotalDiscount;
			bestDiscountIdx = i;
		}
	}

	if (bestPrice > balance)
	{
		std::println("Not enough balance to pay the purchase");
		return;
	}

	balance -= bestPrice;

	Purchase newOrder;
	newOrder.purchaseID = purchases.size() + 1;
	newOrder.boughtPerfumes = cart;
	newOrder.totalPrice = bestPrice;
	newOrder.status = PurchaseStatus::PENDING;

	purchases.push_back(newOrder);

	if (bestDiscountIdx != -1)
	{
		discounts.erase(discounts.begin() + bestDiscountIdx);
	}

	cart.clear(); 
	std::println("Purchase successful! Total price: {}", bestPrice);
}

void Buyer::cancelPurchase(unsigned int purchaseID)
{
	for (auto& currP : purchases)
	{
		if (currP.purchaseID == purchaseID)
		{
			if (currP.status == PurchaseStatus::PENDING)
			{
				currP.status = PurchaseStatus::CANCELED;
				std::println("Purchase ID {} has been successfully canceled", purchaseID);
			}
			else
			{
				std::println("Purchase ID {} cannot be canceled because it is not pending", purchaseID);
			}
			return;
		}
	}

	std::println("Purchase ID {} not found in your history", purchaseID);
}