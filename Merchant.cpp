#include "Merchant.h"
Merchant::Merchant(void)
{
    count = 0;
    SellerList = nullptr;
}
addseller_data Merchant::addSeller(unsigned int pincode)
{
    addseller_data output;
    if (count == 0)
    {
        SellerList = new SellersBlock;
        SellerList->next = nullptr;
        SellerList->data = new Seller[10000];
        SellerList->data[0].id = count + 1;
        SellerList->data[0].locations = new LocationData;
        SellerList->data[0].locations->next = nullptr;
        SellerList->data[0].locations->pins = new unsigned long long int[10]();
        SellerList->data[0].locations->pins[0] = pincode * 1000000000000;
        output.pointer = SellerList->data;
    }
    else
    {
        int location_number = count % 10000;
        SellersBlock *traverse = SellerList;
        while (traverse->next != nullptr)
        {
            traverse = traverse->next;
        }
        if (location_number == 0)
        {
            traverse->next = new SellersBlock;
            traverse = traverse->next;
            traverse->next = nullptr;
            traverse->data = new Seller[10000];
            traverse->data[0].id = count + 1;
            traverse->data[0].locations = new LocationData;
            traverse->data[0].locations->next = nullptr;
            traverse->data[0].locations->pins = new unsigned long long int[10]();
            traverse->data[0].locations->pins[0] = pincode * 1000000000000;
            output.pointer = traverse->data;
        }
        else
        {
            traverse->data[location_number].id = count + 1;
            traverse->data[location_number].locations = new LocationData;
            traverse->data[location_number].locations->next = nullptr;
            traverse->data[location_number].locations->pins = new unsigned long long int[10]();
            traverse->data[location_number].locations->pins[0] = pincode * 1000000000000;
            output.pointer = &(traverse->data[location_number]);
        }
    }
    count++;
    output.id = count;
    return output;
}

Seller *Merchant::addPincode(unsigned long int user_id, unsigned int pincode)
{
    if (user_id > count || user_id<1)
    {
        return nullptr;
    }
    int block_number = (user_id - 1) / 10000;
    int seller_location = (user_id - 1) % 10000;
    SellersBlock *traverse = SellerList;
    for (int i = 0; i < block_number; i++)
    {
        traverse = traverse->next;
    }
    traverse->data[seller_location].addPin(pincode);
    return &(traverse->data[seller_location]);
}
std::vector<unsigned int> Merchant::showLocations(unsigned long int user_id) const
{
    std::vector<unsigned int> output;
    if(user_id>count || user_id<1){
        return output;
    }
    user_id--;
    int block_number = user_id / 10000;
    int seller_location = user_id % 10000;
    SellersBlock *traverse = SellerList;
    for (int i = 0; i < block_number; i++)
    {
        traverse = traverse->next;
    }
    LocationData *location_bock = traverse->data[seller_location].locations;
    int pinlocation;
    unsigned long long int pincode_number;
    unsigned long long int outpush;
    while (location_bock != nullptr)
    {
        pinlocation = 0;
        while (location_bock->pins[pinlocation] != 0 && pinlocation < 10)
        {
            pincode_number = location_bock->pins[pinlocation];
            outpush = pincode_number / 1000000000000;
            output.push_back(outpush);
            pincode_number = pincode_number % 1000000000000;
            if (pincode_number != 0)
            {
                outpush = pincode_number / 1000000;
                output.push_back(outpush);
                pincode_number = pincode_number % 1000000;
            }
            if (pincode_number != 0)
            {
                output.push_back(pincode_number);
                pincode_number = 0;
            }
            pinlocation++;
        }
        location_bock = location_bock->next;
    }
    return output;
}

bool Merchant::isServing(unsigned long int user_id, int pincode) const
{
    user_id--;
    if (user_id < count && user_id>-1)
    {
        int block_number = user_id / 10000;
        int seller_location = user_id % 10000;
        SellersBlock *traverse = SellerList;
        for (int i = 0; i < block_number; i++)
        {
            traverse = traverse->next;
        }
        LocationData *traverse_location = traverse->data[seller_location].locations;
        int first, second, third;
        while (traverse_location != nullptr)
        {
            for (int i = 0; i < 10; i++)
            {
                first = traverse_location->pins[i] / 1000000000000;
                second = traverse_location->pins[i] % 1000000000000;
                third = second % 1000000;
                second = second / 1000000;
                if ((first == pincode) || (second == pincode) || (third == pincode))
                {
                    return true;
                }
            }
            traverse_location = traverse_location->next;
        }
    }
    return false;
}