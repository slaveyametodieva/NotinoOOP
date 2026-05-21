#pragma once
#include "PurchaseStatus.h"
#include <vector>
#include "Fragrance.h"
struct Purchase
{
	unsigned int purchaseID;
	std::vector<Fragrance> boughtPerfumes;
	double totalPrice;
	PurchaseStatus status;

};