#pragma once
#include "addSeller_data.h"
#include "Seller.h"
#include <vector>
#include "SellerBlock.h"
class Merchant
{
private:
    unsigned long int count;
    SellersBlock *SellerList;

public:
    Merchant(void);
    addseller_data addSeller(unsigned int pincode);
    Seller *addPincode(unsigned long int user_id, unsigned int pincode);
    std::vector<unsigned int> showLocations(unsigned long int user_id) const;
    bool isServing(unsigned long int user_id, int pincode) const;
};