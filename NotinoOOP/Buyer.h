#pragma once
#include "User.h"
#include "Fragrance.h"
#include "Purchase.h"
#include <memory>
#include"Discount.h"

constexpr double minBalance = 0.0;
class Buyer : public User
{
	private:
		double balance;
		std::vector<Fragrance> cart;
		std::vector<Fragrance> wishlist;
		std::vector <Purchase> purchases;
		std::vector <std::unique_ptr<Discount>> discounts;

	public:
		Buyer(const std::string& inpUsername, const std::string& inpPassword, double initialBalance);

		void help() const override;

		void addToBalance(double amount);
		void addToWishList(const Fragrance& inpFreg);
		void removeFromWishList(const std::string& fregranceName);

		void addToCart(const Fragrance& addingFreg);
		void removeFromCart(const std::string& inpFregName);

		void viewBought() const;
		void viewPurchase() const;
		void viewCart() const;

};

