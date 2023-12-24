#include "Seller.h"
#include <iostream>
void Seller::addPin(unsigned int pincodes)
{
    unsigned long long int pincode = pincodes;
    LocationData *traverse = locations;
    while (traverse->next != nullptr)
    {
        traverse = traverse->next;
    }
    int position = 9;
    while (traverse->pins[position] == 0)
    {
        position--;
    }
    if (traverse->pins[position] % 1000000000000 == 0)
    {
        traverse->pins[position] =(traverse->pins[position] + (pincode * 1000000));
    }
    else if (traverse->pins[position] % 1000000 == 0)
    {
        traverse->pins[position] = (traverse->pins[position] + pincode);
    }
    else if (position == 9)
    {
        traverse->next = new LocationData;
        traverse = traverse->next;
        traverse->pins = new unsigned long long int[10]();
        traverse->pins[0] = (pincode * 1000000000000);
    }
    else
    {
        traverse->pins[(position + 1)] += (pincode * 1000000000000);
    }
}