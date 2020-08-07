// wbbb.cpp
#include <bits/stdc++.h>

using namespace std;

void init()
{
}

int helpAlice(int x, int y)
{
    for (int i = 0; i < 10; i++)
        if ((x & (1 << i)) != (y & (1 << i)))
            return 2 * i + ((x >> i) & 1) + 1;
    return 0;
}

int helpBob(int z, int k)
{
    k--;
    int b = k >> 1, c = (z >> b) & 1, d = k & 1;
    return c == d;
}