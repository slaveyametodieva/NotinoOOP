#pragma once
#include "AdminCommandBase.h"
#include <vector>
#include "Fragrance.h"
class AddQuantityCommand : public AdminCommandBase
{
	private:
		std::vector<Fragrance>& catalog;

	public:
		AddQuantityCommand(Admin* a, std::vector<Fragrance>& cat);
		void execute() override;
};

