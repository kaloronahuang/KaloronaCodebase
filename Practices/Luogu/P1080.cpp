// P1080.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;
#define ll __int128

struct Minister
{
    int l, r;
    bool operator<(const Minister &m)
    {
        return max(1 / r, l / m.r) < max(1 / m.r, m.l / r);
    }
}

