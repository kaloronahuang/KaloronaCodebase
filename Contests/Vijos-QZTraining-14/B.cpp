// B.cpp
#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

const int MAX_N = 100100, bitnum = 133;

int str[MAX_N], n, m;
char org[MAX_N];
ull hash_str[MAX_N], pow_arr[MAX_N];

ull getHash(int l, int r) { return hash_str[r] - hash_str[l - 1] * pow_arr[r - l + 1]; }

int main()
{
    scanf("%d%d", &n, &m);
    scanf("%s", org + 1), pow_arr[0] = 1;
    for (int i = 1; i <= n; i++)
        str[i] = org[i] - 'A' + 1, hash_str[i] = hash_str[i - 1] * bitnum + str[i], pow_arr[i] = pow_arr[i - 1] * bitnum;
    while (m--)
    {
        int l, r, ans = 0;
        scanf("%d%d", &l, &r);
        for (int i = 20; i >= 0; i--)
            if (l + (1 << i) - 1 <= n && r + (1 << i) - 1 <= n && getHash(l, l + (1 << i) - 1) == getHash(r, r + (1 << i) - 1))
                l += (1 << i), r += (1 << i), ans += (1 << i);
        printf("%d\n", ans);
    }
    return 0;
}