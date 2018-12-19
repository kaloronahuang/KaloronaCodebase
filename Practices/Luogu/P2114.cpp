// P2114.cpp
#include <iostream>
#include <cstdio>
#include <bitset>
using namespace std;
bitset<30> a, b(0x7fffffff), c;
int n, m, tmp;
char opt[10];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%s%d", opt, &tmp);
        if (opt[0] == 'A')
            a &= tmp, b &= tmp;
        else if (opt[0] == 'X')
            a ^= tmp, b ^= tmp;
        else
            a |= tmp, b |= tmp;
    }
    for (int i = 0; i < 30; i++)
        if (a[i] | (b[i] && c.to_ulong() < m))
            c[i] = 1;
    printf("%u", c.to_ulong());
    return 0;
}