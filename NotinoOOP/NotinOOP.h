#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Fragrance.h"
#include "User.h"
#include "Buyer.h"
#include "Admin.h"

class NotinOOP
{
private:
	std::vector<Fragrance> catalog;
	std::vector<std::unique_ptr<User>> allUsers;

	User* loggedInUser;

	void loadData();
	void saveData() const;

	void handleBuyerCommand(Buyer* buyer, const std::string& command);
	void handleAdminCommand(Admin* admin, const std::string& command);

public:
	NotinOOP();
	~NotinOOP();

	void registerBuyer(const std::string& username, const std::string& password);
	void login(const std::string& username, const std::string& password);
	void logout();

	User* getLoggedInUser() const;

	void run();
};