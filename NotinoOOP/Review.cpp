#include "Review.h"
#include <stdexcept>
#include <print>
unsigned int Review::ID = 1;

Review::Review(const std::string& inpAuthorName, const std::string& inpPerfumeName, 
			  unsigned int inpRating, const std::string& inpComment) 
			  : authorName(inpAuthorName), perfumeName(inpPerfumeName), rating(inpRating), comment(inpComment)
{
	if (inpRating > MAX_RATING)
	{
		throw std::invalid_argument("The rating can not be more than 5");
	}

	currReviewID = ID;
	ID++;
}

unsigned int Review::getReviewID() const
{
	return currReviewID;
}

const std::string& Review::getAuthorName() const
{
	return authorName;
}

const std::string& Review::getPerfumeName() const
{
	return perfumeName;
}

unsigned int Review::getRating() const
{
	return rating;
}

const std::string& Review::getComment() const
{
	return comment;
}

void Review::printReview() const
{
	std::println("Review ID {}, written by {} for {} perfume  with rating {} and the comment is: {}",
				currReviewID, authorName, perfumeName,rating, comment);
}
