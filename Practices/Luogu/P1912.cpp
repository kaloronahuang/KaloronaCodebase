// P1912.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_T = 3e6 + 200;
typedef long double ld;

int T, n, L, p, len[MAX_N], pre[MAX_N], q[MAX_N], head, tail, pts[MAX_N];
int sol[MAX_N];
char str[MAX_N][32];
ld dp[MAX_N];

ld quick_pow(ld bas, int tim)
{
    ld ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = ret * bas;
        bas = bas * bas;
        tim >>= 1;
    }
    return ret;
}

ld calc(int i, int j) { return dp[j] + quick_pow(abs(pre[i] - pre[j] - L), p); }

int binary_find(int x, int y)
{
    if (calc(n, x) < calc(n, y))
        return n + 1;
    int l = y, r = n, res = -1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (calc(mid, x) >= calc(mid, y))
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
        memset(pts, 0, sizeof(pts));
        memset(sol, 0, sizeof(sol));
        scanf("%d%d%d", &n, &L, &p), L++;
        for (int i = 1; i <= n; i++)
            scanf("%s", str[i] + 1), len[i] = strlen(str[i] + 1), pre[i] = pre[i - 1] + len[i] + 1, dp[i] = 1e19;
        head = 1, tail = 1, q[1] = 0;
        for (int i = 1; i <= n; i++)
        {
            while (head < tail && pts[head] <= i)
                head++;
            dp[i] = calc(i, q[head]), sol[i] = q[head];
            while (head < tail && pts[tail - 1] >= binary_find(q[tail], i))
                tail--;
            pts[tail] = binary_find(q[tail], i), q[++tail] = i;
        }
        if (dp[n] > 1e18)
            puts("Too hard to arrange");
        else
        {
            printf("%.0Lf\n", dp[n]), head = 0;
            int ptr = q[0] = n;
            while (ptr)
                q[++head] = ptr = sol[ptr];
            for (int i = head; i >= 1; i--)
            {
                // print a line;
                for (int idx = q[i] + 1; idx < q[i - 1]; idx++)
                    printf("%s ", str[idx] + 1);
                puts(str[q[i - 1]] + 1);
            }
        }
        puts("--------------------");
    }
    return 0;
}