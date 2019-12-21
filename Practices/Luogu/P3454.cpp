// P3454.cpp
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

const int MAX_N = 4e5 + 200;

int T, n, xi[MAX_N], yi[MAX_N], len[MAX_N];
ll seq[MAX_N];

ll getDist(int x1, int y1, int x2, int y2)
{
    return ll(x1 - x2) * ll(x1 - x2) + ll(y1 - y2) * ll(y1 - y2);
}

ll getAngle(int orgx, int orgy, int x1, int y1, int x2, int y2)
{
    ll dx1 = x1 - orgx, dy1 = y1 - orgy;
    ll dx2 = x2 - orgx, dy2 = y2 - orgy;
    return dx1 * dy2 - dx2 * dy1;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(len, 0, sizeof(len));
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d%d", &xi[i], &yi[i]);
        // create new string for manacher;
        for (int i = 0; i < n; i++)
        {
            seq[(i << 1) | 1] = getDist(xi[i], yi[i], xi[(i + 1) % n], yi[(i + 1) % n]);
            seq[(i << 1)] = getAngle(xi[i], yi[i], xi[(i + n - 1) % n], yi[(i + n - 1) % n], xi[(i + 1) % n], yi[(i + 1) % n]);
        }
        int tot_len = n << 1;
        for (int i = 0; i < n; i++)
            seq[i + tot_len] = seq[i];
        tot_len <<= 1;
        int R = 0, ans = 0, mid = 0;
        for (int i = 0; i < tot_len; i++)
        {
            if (i < R)
                len[i] = min(R - i, len[mid * 2 - i]);
            else
                len[i] = 1;
            while (i - len[i] >= 0 && i + len[i] < tot_len && seq[i + len[i]] == seq[i - len[i]])
                len[i]++;
            if (i + len[i] > R)
                R = i + len[i], mid = i;
            if (len[i] >= n + 1)
                ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}