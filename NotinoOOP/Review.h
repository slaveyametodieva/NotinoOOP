#pragma once
#include <string>

constexpr int MAX_RATING = 5;

class Review
{
	private:
		static unsigned int ID;
		unsigned int currReviewID;
		std::string authorName;
		std::string perfumeName;
		unsigned int rating;
		std::string comment;

	public:
		Review() = default;
		Review(const std::string& inpAuthorName, const std::string& inpPerfumeName,
			  unsigned int inpRating, const std::string& inpComment);

		unsigned int getReviewID() const;
		const std::string& getAuthorName() const;
		const std::string& getPerfumeName() const;
		unsigned int getRating() const;
		const std::string& getComment() const;

		void printReview() const;

};

