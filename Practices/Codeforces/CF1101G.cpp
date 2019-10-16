// CF1101G.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int ai[MAX_N], prefix[MAX_N], n, base[40];

bool insert(int x)
{
    for (int i = 30; i >= 0; i--)
        if (x & (1 << i))
        {
            if (base[i] == 0)
            {
                base[i] = x;
                return true;
            }
            x ^= base[i];
        }
    return false;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), prefix[i] = ai[i] ^ prefix[i - 1];
    if (prefix[n] == 0)
        printf("-1"), exit(0);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (insert(prefix[i]))
            ans++;
    printf("%d", ans);
    return 0;
}