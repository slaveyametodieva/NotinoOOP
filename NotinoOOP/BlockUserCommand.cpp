#include "BlockUserCommand.h"
#include <string>
#include <iostream>
BlockUserCommand::BlockUserCommand(Admin* a, std::vector<std::unique_ptr<User>>& users): AdminCommandBase(a), allUsers(users)
{
}

void BlockUserCommand::execute()
{
	std::string uName;
	std::cin >> uName;
	admin->blockUser(uName, allUsers);
}
