// Ernd.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1e5 + 200;

map<int, int> mpx, mpy;
map<pr, int> mp;
int n, xi[MAX_N], yi[MAX_N], ans;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &xi[i], &yi[i]), ans += mpx[xi[i]], ans += mpy[yi[i]], ans -= mp[make_pair(xi[i], yi[i])];
        mpx[xi[i]]++, mpy[yi[i]]++, mp[make_pair(xi[i], yi[i])]++;
    }
    printf("%d", ans);
    return 0;
}