#pragma once
#include "Buyer.h"
class ICommand
{
	public:
		virtual ~ICommand() = default;
		virtual void execute() = 0;
};

