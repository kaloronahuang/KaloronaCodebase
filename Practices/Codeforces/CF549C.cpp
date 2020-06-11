// CF549C.cpp
#include <bits/stdc++.h>

using namespace std;

int n, k, cnt[2];

int main()
{
    scanf("%d%d", &n, &k);
    int parity = 0;
    for (int i = 1, val; i <= n; i++)
        scanf("%d", &val), cnt[val & 1]++, parity ^= (val & 1);
    int rem = n - k;
    if (rem == 0)
        puts(parity ? "Stannis" : "Daenerys");
    else if (rem & 1)
    {
        if ((cnt[0] <= (rem >> 1) && (parity ^ ((rem - cnt[0]) & 1)) == 0) || (cnt[1] <= (rem >> 1) && (parity ^ (cnt[1] & 1)) == 0))
            puts("Daenerys");
        else
            puts("Stannis");
    }
    else
    {
        if ((cnt[0] <= (rem >> 1) && (parity ^ ((rem - cnt[0]) & 1))) || (cnt[1] <= (rem >> 1) && (parity ^ (cnt[1] & 1))))
            puts("Stannis");
        else
            puts("Daenerys");
    }

    return 0;
}