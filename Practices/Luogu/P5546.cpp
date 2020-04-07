// P5546.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020, base = 133;

typedef unsigned long long ull;

int n, len[10];
char str[10][MAX_N];
ull hash_val[10][MAX_N], pow_bas[MAX_N];

ull getHash(int id, int l, int r) { return hash_val[id][r] - hash_val[id][l - 1] * pow_bas[r - l + 1]; }

bool check(int mid)
{
    if (mid == 0)
        return true;
    map<ull, int> mp;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= len[i] - mid + 1; j++)
            mp[getHash(i, j, j + mid - 1)] |= (1 << (i - 1));
    for (auto x : mp)
        if (x.second == ((1 << n) - 1))
            return true;
    return false;
}

int main()
{
    scanf("%d", &n), pow_bas[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", str[i] + 1), len[i] = strlen(str[i] + 1);
        for (int j = 1; j <= len[i]; j++)
            hash_val[i][j] = hash_val[i][j - 1] * base + str[i][j] - 'a', pow_bas[j] = pow_bas[j - 1] * base;
    }
    int l = 0, r = *max_element(len + 1, len + 1 + n), res = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, res = mid;
        else
            r = mid - 1;
    }
    printf("%d\n", res);
    return 0;
}