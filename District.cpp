#include "District.h"
District::District(void){
    locals = nullptr;
}
bool District::add(Seller *user, unsigned int pin)
{
    if (locals == nullptr)
    {
        locals = new Local[100];
    }
    return locals[pin].add(user);
}