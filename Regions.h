#pragma once
#include "Seller.h"
#include "District.h"
class Region
{
public:
    District* districts;
    Region(void);
    bool add(Seller* user, unsigned int pin);
};