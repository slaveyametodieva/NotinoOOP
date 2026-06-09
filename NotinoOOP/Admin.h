#pragma once
#include "User.h"
#include "Fragrance.h"
#include <vector>
#include <string>
#include <memory>
#include "Buyer.h"

class Admin : public User
{
public:
	Admin(const std::string& inpUsername, const std::string& inpPassword);

	void help() const override;

	void blockUser(const std::string& deletingUser, std::vector<std::unique_ptr<User>>& allUsers);
	void createFragrance(const std::string& name, Brand brand, double price, FregranceFamily family, 
						std::vector<Fragrance>& catalog);
	void addQuantity(const std::string& fragranceName, unsigned int quantity, std::vector<Fragrance>& catalog);
	void deliver(unsigned int purchaseID, std::vector<std::unique_ptr<User>>& allUsers);
	void removeReview(unsigned int fregranceID, unsigned int reviewID, std::vector<Fragrance>& catalog, 
						std::vector<std::unique_ptr<User>>& allUsers);
};