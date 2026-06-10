#pragma once
#include "ICommand.h"
#include "Admin.h"
class AdminCommandBase : public ICommand
{
	protected:
		Admin* admin;

	public:
		AdminCommandBase(Admin* a);
};

