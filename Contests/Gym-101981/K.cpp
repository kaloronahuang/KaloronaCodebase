// K.cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    for (int cycle = 49900; cycle >= 0; cycle--)
    {
        int rd = rand() % 4;
        if (rd == 0)
            putchar('U');
        else if (rd == 1)
            putchar('L');
        else if (rd == 2)
            putchar('R');
        else
            putchar('D');
    }
    return 0;
}