#include "NotinOOP.h"
#include <iostream>
#include <fstream>
#include <print>

NotinOOP::NotinOOP() : loggedInUser(nullptr)
{
	loadData();

	if (allUsers.empty())
	{
		allUsers.push_back(std::make_unique<Admin>("admin", "admin123"));
	}
}

NotinOOP::~NotinOOP()
{
	saveData();
}

void NotinOOP::registerBuyer(const std::string& username, const std::string& password)
{
	for (const auto& u : allUsers)
	{
		if (u->getUsername() == username)
		{
			std::println("Error: The username '{}' is already taken.", username);
			return;
		}
	}
	allUsers.push_back(std::make_unique<Buyer>(username, password, 0.0));
	std::println("Registration successful! You can now log in as '{}'.", username);
}

void NotinOOP::login(const std::string& username, const std::string& password)
{
	if (loggedInUser != nullptr)
	{
		std::println("Error: Someone is already logged in. Please log out first.");
		return;
	}

	for (const auto& u : allUsers)
	{
		if (u->getUsername() == username)
		{
			if (u->checkPassword(password))
			{
				loggedInUser = u.get();
				std::println("Welcome back, {}!", username);
				return;
			}
			else
			{
				std::println("Error: Incorrect password.");
				return;
			}
		}
	}
	std::println("Error: User '{}' not found.", username);
}

void NotinOOP::logout()
{
	if (loggedInUser != nullptr)
	{
		std::println("Goodbye, {}!", loggedInUser->getUsername());
		loggedInUser = nullptr;
	}
	else
	{
		std::println("No user is currently logged in.");
	}
}

User* NotinOOP::getLoggedInUser() const
{
	return loggedInUser;
}

void NotinOOP::run()
{
	std::string command;
	std::println("Welcome to NotinOOP! Type 'register', 'login', or 'exit'.");

	while (true)
	{
		std::cout << "> ";
		std::cin >> command;

		if (loggedInUser == nullptr)
		{
			if (command == "exit") {
				std::println("Exiting NotinOOP...");
				break;
			}
			else if (command == "register") {
				std::string username, password;
				std::cin >> username >> password;
				registerBuyer(username, password);
			}
			else if (command == "login") {
				std::string username, password;
				std::cin >> username >> password;
				login(username, password);
			}
			else {
				std::println("You must be logged in. (Available: register, login, exit)");
			}
		}
		else
		{
			if (command == "exit") {
				std::println("Exiting NotinOOP...");
				break;
			}
			else if (command == "logout") {
				logout();
			}
			else if (command == "help") {
				loggedInUser->help();
			}
			else
			{
				Buyer* buyerPtr = dynamic_cast<Buyer*>(loggedInUser);
				Admin* adminPtr = dynamic_cast<Admin*>(loggedInUser);

				if (buyerPtr != nullptr) {
					handleBuyerCommand(buyerPtr, command);
				}
				else if (adminPtr != nullptr) {
					handleAdminCommand(adminPtr, command);
				}
			}
		}
	}
}

void NotinOOP::handleBuyerCommand(Buyer* buyer, const std::string& command)
{
	if (command == "add-to-balance") {
		double amount; 
		std::cin >> amount;
		buyer->addToBalance(amount);
		std::println("Added {} to your balance.", amount);
	}
	else if (command == "view-cart") {
		buyer->viewCart();
	}
	else if (command == "checkout") {
		buyer->checkout();
	}
	else if (command == "recommend") {
		buyer->recommend(catalog);
	}
	else if (command == "add-to-cart") {
		std::string fName;
		std::cin >> fName;

		bool found = false;

		for (const auto& perf : catalog) {
			if (perf.getPName() == fName) {
				buyer->addToCart(perf);
				std::println("Added '{}' to cart.", fName);
				found = true;
				break;
			}
		}
		if (!found) 
			std::println("Error: '{}' not found.", fName);
	}
	else if (command == "add-to-wishlist") {
		std::string fName;
		std::cin >> fName;

		bool found = false;

		for (const auto& perf : catalog) {
			if (perf.getPName() == fName) {
				buyer->addToWishList(perf);
				std::println("Added '{}' to wishlist.", fName);
				found = true; break;
			}
		}
		if (!found) std::println("Error: '{}' not found.", fName);
	}
	else if (command == "remove-from-wishlist") {
		std::string fName;
		std::cin >> fName;

		buyer->removeFromWishList(fName);
		std::println("Removed '{}' from wishlist.", fName);
	}
	else if (command == "remove-from-cart") {
		std::string fName;
		std::cin >> fName;

		buyer->removeFromCart(fName);
		std::println("Removed '{}' from cart.", fName);
	}
	else if (command == "view-bought") {
		buyer->viewBought();
	}
	else if (command == "view-purchases") {
		buyer->viewPurchase();
	}
	else if (command == "cancel") {
		unsigned int pId;	
		std::cin >> pId;
		buyer->cancelPurchase(pId);
	}
	else if (command == "make-review") {
		std::string fName;
		double rating;
		std::string comment;

		std::cin >> fName >> rating;
		std::cin.ignore();
		std::getline(std::cin, comment);

		if (!comment.empty() && comment[0] == ' ')
			comment = comment.substr(1);

		bool found = false;

		for (auto& perf : catalog) {
			if (perf.getPName() == fName) {
				static unsigned int rId = 1;
				Review newReview(buyer->getUsername(), perf.getPName(), rating, comment);
				perf.addReview(newReview);
				std::println("Review added for '{}'!", fName);

				found = true;
				break;
			}
		}
		if (!found) 
			std::println("Error: '{}' not found.", fName);
	}
	else {
		std::println("Invalid command. Type 'help'.");
	}
}

void NotinOOP::handleAdminCommand(Admin* admin, const std::string& command)
{
	if (command == "block-user") {
		std::string uName; 
		std::cin >> uName;

		admin->blockUser(uName, allUsers);
	}
	else if (command == "add-quantity") {
		std::string fName; 
		unsigned int qty; 
		std::cin >> fName >> qty;

		admin->addQuantity(fName, qty, catalog);
	}
	else if (command == "deliver") {
		unsigned int pId; 
		std::cin >> pId;
		admin->deliver(pId, allUsers);
	}
	else if (command == "create-fragrance") {
		std::string name;
		int brandInt, familyInt; 
		double price;
		std::cin >> name >> brandInt >> price >> familyInt;
		Brand b = static_cast<Brand>(brandInt);
		FregranceFamily f = static_cast<FregranceFamily>(familyInt);
		admin->createFragrance(name, b, price, f, catalog);
	}
	else if (command == "remove-review") {
		unsigned int fId, rId; 
		std::cin >> fId >> rId;
		admin->removeReview(fId, rId, catalog, allUsers);
	}
	else {
		std::println("Invalid command. Type 'help'.");
	}
}

void NotinOOP::saveData() const
{
	std::ofstream catalogFile("catalog.txt");
	if (catalogFile.is_open()) {
		catalogFile << catalog.size() << '\n';

		for (const auto& f : catalog) {
			catalogFile << f.getPName() << '\n'
				<< static_cast<int>(f.getBrand()) << '\n'
				<< f.getPPrice() << '\n'
				<< static_cast<int>(f.getFFamily()) << '\n'
				<< f.getQuantity() << '\n';
		}
	}

	std::ofstream usersFile("users.txt");
	if (usersFile.is_open()) {
		usersFile << allUsers.size() << '\n';

		for (const auto& u : allUsers) {
			Admin* adminPtr = dynamic_cast<Admin*>(u.get());
			if (adminPtr) {
				usersFile << "[ADMIN]\n" << adminPtr->getUsername() << '\n' << adminPtr->getRemovedReviewsCount() << '\n';
			}
			else {
				Buyer* buyerPtr = dynamic_cast<Buyer*>(u.get());
				if (buyerPtr) {
					usersFile << "[BUYER]\n" << buyerPtr->getUsername() << '\n' << buyerPtr->getRemovedReviewsCount() << '\n';
				}
			}
		}
	}
}

void NotinOOP::loadData()
{
	std::ifstream catalogFile("catalog.txt");
	if (catalogFile.is_open()) {
		size_t catSize;

		if (catalogFile >> catSize) {
			for (size_t i = 0; i < catSize; ++i) {
				std::string name; 
				int bInt, fInt; double price;
				unsigned int qty;

				catalogFile >> std::ws;
				std::getline(catalogFile, name);
				catalogFile >> bInt >> price >> fInt >> qty;
				std::vector<Review> emptyReviews;
				catalog.emplace_back(name, price, static_cast<FregranceFamily>(fInt), qty, static_cast<Brand>(bInt), 
									emptyReviews);
			}
		}
	}

	std::ifstream usersFile("users.txt");
	if (usersFile.is_open()) {
		size_t uSize;
		if (usersFile >> uSize) {
			for (size_t i = 0; i < uSize; ++i) {
				std::string type;
				usersFile.ignore();
				std::getline(usersFile, type);

				std::string uname;
				unsigned int remRev;
				usersFile.ignore();
				std::getline(usersFile, uname);

				usersFile >> remRev;
				if (type == "[ADMIN]") {
					allUsers.push_back(std::make_unique<Admin>(uname, "admin123"));
				}
				else if (type == "[BUYER]") {
					allUsers.push_back(std::make_unique<Buyer>(uname, "buyer123", 0.0));
				}
			}
		}
	}
}