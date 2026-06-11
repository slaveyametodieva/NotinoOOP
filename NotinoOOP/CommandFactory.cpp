#include "CommandFactory.h"

#include "AddToBalanceCommand.h"
#include "ViewCartCommand.h"
#include "ChekoutCommand.h"
#include "RecommendCommand.h"
#include "AddToCartCommand.h"
#include "AddToWishlistCommand.h"
#include "RemoveFromWishlistCommand.h"
#include "RemoveFromCartCommand.h"
#include "ViewBoughtCommand.h"
#include "ViewPurchasesCommand.h"
#include "CancelPurchaseCommand.h"
#include "MakeReviewCommand.h"

#include "BlockUserCommand.h"
#include "AddQuantityCommand.h"
#include "DeliverCommand.h"
#include "CreateFragranceCommand.h"
#include "RemoveReviewCommand.h"
std::unique_ptr<ICommand> CommandFactory::createBuyerCommand(const std::string& commandName, Buyer* buyer, std::vector<Fragrance>& catalog)
{
	if (commandName == "add-to-balance")       return std::make_unique<AddToBalanceCommand>(buyer);
	if (commandName == "view-cart")            return std::make_unique<ViewCartCommand>(buyer);
	if (commandName == "checkout")             return std::make_unique<ChekoutCommand>(buyer);
	if (commandName == "recommend")            return std::make_unique<RecommendCommand>(buyer, catalog);
	if (commandName == "add-to-cart")          return std::make_unique<AddToCartCommand>(buyer, catalog);
	if (commandName == "add-to-wishlist")      return std::make_unique<AddtoWishlistCommand>(buyer, catalog);
	if (commandName == "remove-from-wishlist") return std::make_unique<RemoveFromWishListCommand>(buyer);
	if (commandName == "remove-from-cart")     return std::make_unique<RemoveFromCartCommand>(buyer);
	if (commandName == "view-bought")          return std::make_unique<ViewBoughtCommand>(buyer);
	if (commandName == "view-purchases")       return std::make_unique<ViewPurchasesCommand>(buyer);
	if (commandName == "cancel")               return std::make_unique<CancelPurchaseCommand>(buyer);
	if (commandName == "make-review")          return std::make_unique<MakeReviewCommand>(buyer, catalog);

	return nullptr;
}

std::unique_ptr<ICommand> CommandFactory::createAdminCommand(const std::string& commandName, Admin* admin, std::vector<Fragrance>& catalog, std::vector<std::unique_ptr<User>>& allUsers)
{
	if (commandName == "block-user")       return std::make_unique<BlockUserCommand>(admin, allUsers);
	if (commandName == "add-quantity")     return std::make_unique<AddQuantityCommand>(admin, catalog);
	if (commandName == "deliver")          return std::make_unique<DeliverCommand>(admin, allUsers);
	if (commandName == "create-fragrance") return std::make_unique<CreateFragranceCommand>(admin, catalog);
	if (commandName == "remove-review")    return std::make_unique<RemoveReviewCommand>(admin, catalog, allUsers);

	return nullptr;
}
