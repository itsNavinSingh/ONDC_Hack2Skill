#pragma once
#include "Seller.h"
#include "PinSeller.h"
class Local
{
public:
    PinSeller* data;
    Local(void);
    bool add(Seller*);
};
