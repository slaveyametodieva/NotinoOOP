#include "RemoveReviewCommand.h"

RemoveReviewCommand::RemoveReviewCommand(Admin* a, std::vector<Fragrance>& cat,
	std::vector<std::unique_ptr<User>>& users): AdminCommandBase(a), catalog(cat), allUsers(users)
{
}
