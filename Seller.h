#pragma once
#include "LocationData.h"
class Seller
{
public:
    unsigned long int id;
    LocationData *locations;
    void addPin(unsigned int);
};