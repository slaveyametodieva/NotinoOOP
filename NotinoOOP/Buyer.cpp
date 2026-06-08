#include "Buyer.h"
#include <stdexcept>
#include <print>
#include <algorithm>
#include <iostream>
Buyer::Buyer(const std::string& inpUsername, const std::string& inpPassword, double initialBalance):
	User(inpUsername, inpPassword)
{
	if (initialBalance < minBalance)
	{
		throw std::invalid_argument("The balance can not be a negative number");
	}
	balance = initialBalance;
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
