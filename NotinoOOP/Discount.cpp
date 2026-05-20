#include "Discount.h"
#include <stdexcept>
unsigned int Discount::ID = 1;
Discount::Discount(double inpPercantage): disPercantage(inpPercantage)
{
    if (disPercantage < minPercantage || disPercantage > maxPercantage)
    {
        throw std::invalid_argument("The percantage can ot ne a negative number");
    }
    currDID = ID;
    ID++;
}


unsigned int Discount::getCurrDID() const
{
    return currDID;
}
