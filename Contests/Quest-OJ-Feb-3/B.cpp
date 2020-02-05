// B.cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7;

int n, seq[MAX_N], dp[MAX_N];
deque<int> tmp;

int getLIS(bool mode = false)
{
    int cur = 0;
    dp[0] = -0x3f3f3f3f;
    for (int i = 0; i < n; i++)
    {
        if (tmp[i] > dp[cur] || (mode && tmp[i] >= dp[cur]))
            dp[++cur] = tmp[i];
        else
            *(lower_bound(dp + 1, dp + 1 + cur, tmp[i])) = tmp[i];
    }
    return cur;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    if (n <= 20)
    {
        int max_len = 0, ans = 0;
        for (int stat = 0; stat < (1 << (n - 1)); stat++)
        {
            tmp.clear();
            tmp.push_front(seq[1]);
            for (int i = 1; i < n; i++)
                if (stat & (1 << (i - 1)))
                    tmp.push_back(seq[i + 1]);
                else
                    tmp.push_front(seq[i + 1]);
            max_len = max(getLIS(), max_len);
        }
        for (int stat = 0; stat < (1 << (n - 1)); stat++)
        {
            tmp.clear();
            tmp.push_front(seq[1]);
            for (int i = 1; i < n; i++)
                if (stat & (1 << (i - 1)))
                    tmp.push_back(seq[i + 1]);
                else
                    tmp.push_front(seq[i + 1]);
            if (getLIS() == max_len)
            {
                for (int i = 0; i < n; i++)
                    tmp[i] = -tmp[i];
                ans = (0LL + ans + getLIS(true)) % mod;
            }
        }
        printf("%d %d\n", max_len, ans);
    }
    else
    {
    }
    return 0;
}