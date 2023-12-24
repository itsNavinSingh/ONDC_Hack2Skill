#include "Regions.h"
Region::Region(void){
    districts = nullptr;
}
bool Region::add(Seller *user, unsigned int pin)
{
    unsigned int insider_pin = pin / 100;
    if (districts == nullptr)
    {
        districts = new District[100];
    }
    return districts[insider_pin].add(user, pin % 100);
}