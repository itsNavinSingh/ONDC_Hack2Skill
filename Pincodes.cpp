#include "Pincodes.h"
Pincodes::Pincodes(void)
{
    regions = nullptr;
}
bool Pincodes::add(Seller *user, unsigned int pin)
{
    unsigned int insider_pin = (pin / 10000) - 11;
    if (regions == nullptr)
    {
        regions = new Region[75];
    }
    return regions[insider_pin].add(user, pin % 10000);
}

std::vector<unsigned long int> Pincodes::showSellers(unsigned int pin)
{
    std::vector<unsigned long int> output;
    unsigned int level1, level2, level3;
    level1 = (pin / 10000) - 11;
    level3 = pin % 100;
    level2 = (pin / 100) % 100;
    // if ((regions != nullptr) && (regions[level1].districts != nullptr) &&
    // (regions[level1].districts[level2].locals != nullptr) &&
    // (regions[level1].districts[level2].locals[level3].data != nullptr))
    if (regions != nullptr)
    {
        if (regions[level1].districts != nullptr)
        {
            if (regions[level1].districts[level2].locals != nullptr)
            {
                if ((regions[level1].districts[level2].locals[level3].data != nullptr))
                {
                    PinSeller *traverse = regions[level1].districts[level2].locals[level3].data;
                    while (traverse != nullptr)
                    {
                        output.push_back(traverse->seller_info->id);
                        traverse = traverse->next;
                    }
                }
            }
        }
    }
    return output;
}