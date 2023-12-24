#include "Local.h"
Local::Local(void){
    data = nullptr;
}
bool Local::add(Seller *user)
{
    PinSeller *newdata = new PinSeller;
    newdata->seller_info = user;
    if (data == nullptr)
    {
        newdata->next = nullptr;
        data = newdata;
    }
    else if (data->seller_info->id > user->id)
    {
        newdata->next = data;
        data = newdata;
    }
    else
    {
        PinSeller *traverse = data;
        PinSeller *prev = nullptr;
        while (traverse != nullptr && traverse->seller_info->id < user->id)
        {
            prev = traverse;
            traverse = traverse->next;
        }
        prev->next = newdata;
        newdata->next = traverse;
    }
    return true;
}