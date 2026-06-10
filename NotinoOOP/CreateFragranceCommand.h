#pragma once
#include "AdminCommandBase.h"
#include "Fragrance.h"
#include <vector>
#include <memory>

class CreateFragranceCommand : public AdminCommandBase
{
	private:
		std::vector<Fragrance>& catalog;

	public:
		CreateFragranceCommand(Admin* a, std::vector<Fragrance>& cat);
		void execute() override;

};

