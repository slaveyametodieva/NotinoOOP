#include "User.h"
#include <stdexcept>
#include <print>
unsigned int User::ID = 1;

User::User(const std::string& inpUsername, const std::string& inpPassword): username(inpUsername),
			password(inpPassword)
{
	personalID = ID;
	ID++;


}

void User::incerementRemovedReviews()
{
	removedReviews++;
}

unsigned int User::getRemovedReviewsCount() const
{
	return removedReviews;
}

unsigned int User::getPersonalID() const
{
	return personalID;
}

const std::string& User::getUsername() const
{
	return username;
}

bool User::checkPassword(const std::string& inpPassword) const
{
	return password == inpPassword;
}

