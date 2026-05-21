#pragma once
#include <string>
#include <vector>

class User
{
	private:
		static unsigned int ID;
		unsigned int personalID;
		std::string username;
		std::string password;

	public:
		virtual ~User() = default;
		User(const std::string& inpUsername, const std::string& inpPassword);
		
		unsigned int getPersonalID() const;
		const std::string& getUsername() const;

		bool checkPassword(const std::string& inpPassword) const;
		virtual void help()const = 0;


};

