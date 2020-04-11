// D.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200;

int T, n;
ll l, r, f[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%lld%lld", &n, &l, &r);
        int lpos, lbias;
        for (int i = 1; i <= n; i++)
            f[i] = (0LL + f[i - 1] + ((1LL * (n - i)) << 1));
        if (l == 1LL * n * (n - 1) + 1)
        {
            puts("1");
            continue;
        }
        for (int i = 1; i <= n; i++)
            if (f[i - 1] < l && l <= f[i])
                lpos = i, lbias = l - f[i - 1];
        bool flag = r == 1LL * n * (n - 1) + 1;
        if (flag)
            r--;
        while (l <= r)
        {
            if (l & 1)
                printf("%d ", lpos);
            else
                printf("%d ", (lbias >> 1) + lpos);
            l++, lbias++;
            if (lbias > ((n - lpos) << 1))
                lbias = 1, lpos++;
        }
        if (flag)
            puts("1");
        else
            puts("");
    }
    return 0;
}