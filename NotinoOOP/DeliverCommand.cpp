#include "DeliverCommand.h"
#include <iostream>
DeliverCommand::DeliverCommand(Admin* a, std::vector<std::unique_ptr<User>>& users): AdminCommandBase(a), allUsers(users)
{
}

void DeliverCommand::execute()
{
	unsigned int pId;
	std::cin >> pId;

	admin->deliver(pId, allUsers);
}
