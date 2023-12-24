#pragma once
#include "Seller.h"
#include "Local.h"
class District
{
public:
    Local* locals;
    District(void);
    bool add(Seller*, unsigned int);
};

