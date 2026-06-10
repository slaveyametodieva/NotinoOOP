#pragma once
#include "AdminCommandBase.h"
#include "User.h"
#include <memory>
#include <vector>
class BlockUserCommand : public AdminCommandBase
{
	private:
		std::vector<std::unique_ptr<User>>& allUsers;

	public:
		BlockUserCommand(Admin* a, std::vector<std::unique_ptr<User>>& users);
		void execute() override;
};

