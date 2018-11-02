// P1010.cpp
#include <iostream>
#include <cmath>

using namespace std;

string calc(int i)
{
    if (i == 2)
        return "2";
    if (i % 2 == 1)
        return calc(i - 1) + "+2(0)";
    else
    {
        double l = log2(i);
        int lfloor = (int)l;
        if (l == lfloor)
            return "2(" + calc(lfloor) + ")";
        else
            return "2(" + calc(lfloor) + ")+" + calc(i - pow(2, lfloor));
    }
}

int main()
{
    int n;
    cin >> n;
    cout << calc(n);
    return 0;
}