#include <iostream>

using namespace std;

struct BigInt
{
    string base;

    string operator=()
    {
        return this->base;
    }

    bool operator==(BigInt bi)
    {
        return bi.base == this->base;
    }

    bool operator!=(BigInt bi)
    {
        return bi.base != this->base;
    }

    bool operator>(BigInt bi)
    {
        if (bi.base.length() < this->base.length())
            return true;
        if (bi.base.length() > this->base.length())
            return false;
        for (int i = 0; i < bi.length(); i++)
            if (this->base[i] > bi.base[i])
                return true;
            else if (this->base[i] < bi.base[i])
                return false;
        return false;
    }

    bool operator>=(BigInt bi)
    {
        return (*this > bi) || (*this == bi);
    }
};

int main()
{
    return 0;
}
