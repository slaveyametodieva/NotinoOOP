#pragma once
#include "AdminCommandBase.h"
#include "User.h"
#include <vector>
#include <memory>
class DeliverCommand : public AdminCommandBase
{
	private:
		std::vector<std::unique_ptr<User>>& allUsers;

	public:
		DeliverCommand(Admin* a, std::vector<std::unique_ptr<User>>& users);
		void execute() override;
};

