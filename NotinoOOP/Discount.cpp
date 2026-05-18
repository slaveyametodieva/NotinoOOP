#include "Discount.h"
#include <stdexcept>
unsigned int Discount::ID = 1;
Discount::Discount(double inpPercantage): percantage(inpPercantage)
{
    if (percantage < minPercantage)
    {
        throw std::invalid_argument("The percantage can ot ne a negative number");
    }
    currDID = ID;
    ID++;
}
double Discount::getPercantage() const
{
    return percantage;
}

unsigned int Discount::getCurrDID() const
{
    return currDID;
}
