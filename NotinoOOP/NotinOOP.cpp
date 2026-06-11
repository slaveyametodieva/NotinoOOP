#include "NotinOOP.h"
#include "CommandFactory.h" 
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
				std::println("Exiting NotinOOP..");
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
				std::println("Exiting NotinOOP... Goodbye!");
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
	std::unique_ptr<ICommand> cmd = CommandFactory::createBuyerCommand(command, buyer, catalog);

	if (cmd != nullptr)
	{
		cmd->execute();
	}
	else
	{
		std::println("Invalid command. Type 'help' to see the available commands.");
	}
}

void NotinOOP::handleAdminCommand(Admin* admin, const std::string& command)
{
	std::unique_ptr<ICommand> cmd = CommandFactory::createAdminCommand(command, admin, catalog, allUsers);

	if (cmd != nullptr)
	{
		cmd->execute();
	}
	else
	{
		std::println("Invalid Admin command. Type 'help' to see the available commands.");
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
				std::string name; int bInt, fInt; double price; unsigned int qty;
				catalogFile >> std::ws;
				std::getline(catalogFile, name);
				catalogFile >> bInt >> price >> fInt >> qty;
				std::vector<Review> emptyReviews;
				catalog.emplace_back(name, price, static_cast<FregranceFamily>(fInt), qty, static_cast<Brand>(bInt), emptyReviews);
			}
		}
	}

	std::ifstream usersFile("users.txt");
	if (usersFile.is_open()) {

		size_t uSize;

		if (usersFile >> uSize) {
			for (size_t i = 0; i < uSize; ++i) {
				std::string typeMarker;
				usersFile.ignore();
				std::getline(usersFile, typeMarker);

				std::string uname;
				unsigned int remRev;
				usersFile.ignore();
				std::getline(usersFile, uname);
				usersFile >> remRev;

				if (typeMarker == "[ADMIN]") {
					allUsers.push_back(std::make_unique<Admin>(uname, "admin123"));
				}
				else if (typeMarker == "[BUYER]") {
					allUsers.push_back(std::make_unique<Buyer>(uname, "buyer123", 0.0));
				}
			}
		}
	}
}