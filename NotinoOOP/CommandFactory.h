#pragma once
#include <memory>
#include <string>
#include <vector>

#include "ICommand.h"
#include "Buyer.h"
#include "Admin.h"
#include "Fragrance.h"

class CommandFactory
{
public:
	static std::unique_ptr<ICommand> createBuyerCommand(const std::string& commandName, 
		Buyer* buyer, std::vector<Fragrance>& catalog);
	static std::unique_ptr<ICommand> createAdminCommand(const std::string& commandName, 
		Admin* admin, std::vector<Fragrance>& catalog, std::vector<std::unique_ptr<User>>& allUsers);
};