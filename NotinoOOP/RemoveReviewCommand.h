#pragma once
#include "AdminCommandBase.h"
#include <vector>
#include "Fragrance.h"
#include "User.h"
class RemoveReviewCommand : public AdminCommandBase
{
	private:
		std::vector<Fragrance>& catalog;
		std::vector<std::unique_ptr<User>>& allUsers;

	public:
		RemoveReviewCommand(Admin* a, std::vector<Fragrance>& cat, std::vector<std::unique_ptr<User>>& users);
		void execute() override;
};

