// BZ1563.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;
const char *breakLine = "--------------------";

typedef long double ll;

int T, n, len, p, q[MAX_N], chosen[MAX_N], rig[MAX_N];
char poem[MAX_N][32];
ll dp[MAX_N], pre[MAX_N];

ll quick_pow(ll bas, int tim)
{
    ll ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = ret * bas;
        bas = bas * bas;
        tim >>= 1;
    }
    return ret;
}

ll getDP(int i, int j) { return dp[j] + quick_pow(llabs(pre[i] - pre[j] - 1 - len), p); }

int binaryFind(int x, int y)
{
    if (getDP(n, x) < getDP(n, y))
        return n + 1;
    int l = y, r = n, res;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (getDP(mid, x) >= getDP(mid, y))
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    return res;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &len, &p);
        for (int i = 1; i <= n; i++)
            scanf("%s", poem[i] + 1), pre[i] = strlen(poem[i] + 1) + pre[i - 1];
        for (int i = 1; i <= n; i++)
            pre[i] += i;

        int head = 1, tail = 1;
        q[1] = 0;
        for (int i = 1; i <= n; i++)
        {
            while (head < tail && rig[head] <= i)
                head++;
            dp[i] = getDP(i, q[head]), chosen[i] = q[head];
            while (head < tail && rig[tail - 1] >= binaryFind(q[tail], i))
                tail--;
            rig[tail] = binaryFind(q[tail], i), q[++tail] = i;
        }
        if (dp[n] > 1e18)
            puts("Too hard to arrange");
        else
            printf("%.0Lf\n", dp[n]);
        printf("%s\n", breakLine);
    }
    return 0;
}