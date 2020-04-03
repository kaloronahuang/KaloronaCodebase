// ARC098B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, ai[MAX_N], bits[20][MAX_N];
long long ans;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 20; j++)
            bits[j][i] = bits[j][i - 1] + ((ai[i] >> j) & 1);
    for (int i = 1; i <= n; i++)
    {
        int l = 1, r = i, res;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            bool flag = true;
            for (int j = 0; j < 20; j++)
                flag &= bits[j][i] - bits[j][mid - 1] <= 1;
            if (flag)
                r = mid - 1, res = mid;
            else
                l = mid + 1;
        }
        ans += i - res + 1;
    }
    printf("%lld\n", ans);
    return 0;
}