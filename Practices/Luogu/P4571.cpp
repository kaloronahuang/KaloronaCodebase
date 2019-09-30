// P4571.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

map<int, int> mp;
int n, seq[MAX_N], ans, k;

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &seq[i]);
        int tmp = seq[i];
        for (int j = 1; 1LL * j * j <= tmp; j++)
        {
            if (tmp % j == 0)
                mp[j]++;
            if (tmp % j == 0 && (tmp / j) != j)
                mp[tmp / j]++;
        }
    }
    for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
        if (it->second >= k)
            ans = max(ans, it->first);
    printf("%d", ans);
    return 0;
}