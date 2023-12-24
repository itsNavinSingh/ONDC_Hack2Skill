#pragma once
#include <vector>
#include "Seller.h"
#include "Regions.h"
class Pincodes
{
public:
    Region* regions;
    Pincodes(void);
    bool add(Seller* user, unsigned int pin);
    std::vector<unsigned long int> showSellers(unsigned int pin);
};