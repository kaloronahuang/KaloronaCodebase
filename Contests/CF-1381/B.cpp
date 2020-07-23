// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4020;

int T, n, pi[MAX_N];
bool dp[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(dp, 0, sizeof(dp));
        scanf("%d%d", &n, &pi[1]);
        int preMax = pi[1], lastPtr = 1;
        vector<int> inv;
        pi[(n << 1) | 1] = (n << 1) | 1;
        for (int i = 2; i <= (n << 1) + 1; i++)
        {
            if (i <= (n << 1))
                scanf("%d", &pi[i]);
            if (max(preMax, pi[i]) != preMax)
                inv.push_back(i - lastPtr), preMax = pi[i], lastPtr = i;
        }
        dp[0] = true;
        for (int x : inv)
            for (int j = n << 1; j >= x; j--)
                dp[j] |= dp[j - x];
        puts(dp[n] ? "YES" : "NO");
    }
    return 0;
}