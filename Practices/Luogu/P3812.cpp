// P3812.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 55;
ll arr[MAX_N], n, bit[70], ans;

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &arr[i]);
        for (int pt = 62; pt >= 0; pt--)
        {
            if (((arr[i] >> (ll)pt) & 1) == 0)
                continue;
            if (bit[pt] == 0)
            {
                bit[pt] = arr[i];
                break;
            }
            arr[i] ^= bit[pt];
        }
    }
    for (int i = 62; i >= 0; i--)
        if ((ans ^ bit[i]) > ans)
            ans ^= bit[i];
    printf("%lld", ans);
    return 0;
}