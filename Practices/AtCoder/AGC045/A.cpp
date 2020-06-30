// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220;

typedef long long ll;

int T, n;
ll base[MAX_N], ai[MAX_N];
char str[MAX_N];

void insert(ll x)
{
    for (int i = 62; i >= 0; i--)
        if (x & (1LL << i))
        {
            if (base[i] == 0)
            {
                base[i] ^= x;
                break;
            }
            x ^= base[i];
        }
}

bool query(ll x)
{
    for (int i = 62; i >= 0; i--)
        if (x & (1LL << i))
            x ^= base[i];
    return x == 0;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &ai[i]);
        scanf("%s", str + 1);
        for (int i = 0; i <= 62; i++)
            base[i] = 0;
        bool flag = false;
        for (int i = n; i >= 1; i--)
        {
            if (str[i] == '0')
                insert(ai[i]);
            else if (!query(ai[i]))
            {
                flag = true;
                break;
            }
        }
        puts(flag ? "1" : "0");
    }
    return 0;
}