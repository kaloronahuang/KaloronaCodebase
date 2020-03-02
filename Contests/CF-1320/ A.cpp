// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, bi[MAX_N];
map<int, vector<int> /**/ > mp;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &bi[i]), mp[i - bi[i]].push_back(i);
    long long ans = 0;
    for (auto &x : mp)
    {
        long long sum = 0;
        for (auto &y : x.second)
            sum += bi[y];
        ans = max(ans, sum);
    }
    printf("%lld\n", ans);
    return 0;
}