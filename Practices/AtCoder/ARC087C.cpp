// ARC087C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n;
map<int, int> mp;

int main()
{
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++)
        scanf("%d", &x), mp[x]++;
    long long ans = 0;
    for (auto x : mp)
        if (x.first > x.second)
            ans += x.second;
        else if (x.first < x.second)
            ans += x.second - x.first;
    printf("%d\n", ans);
    return 0;
}