// P4749.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 510;

int n, tot;
short rot[MAX_N], bucket[10], stats[MAX_N][4], dp[MAX_N][MAX_N][MAX_N];
char opt[10];

int main()
{
    scanf("%d", &n), tot++;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", opt);
        int now = 0;
        bool flag = false;
        for (int ptr = 0; ptr < 7; ptr++)
        {
            if (ptr > 0 && opt[ptr] != opt[ptr - 1])
                flag = true;
            int tmp = 0;
            for (int k = 0; k < 7; k++)
                tmp = tmp * 10 + opt[(ptr + k) % 7] - '0';
            if (tmp > now)
                now = tmp, rot[tot] = ptr;
        }
        if (flag)
            tot++;
    }
    for (int i = tot; i >= 1; i--)
        rot[i] = (rot[i] - rot[i - 1] + 7) % 7, bucket[rot[i]]++;

    int ans = 0, x = 1, y = 2, z = 3;
    int t = min(bucket[1], bucket[6]);
    ans += t;
    if (bucket[1] -= t)
        x = 1;
    if (bucket[6] -= t)
        x = 6;

    t = min(bucket[2], bucket[5]);
    ans += t;
    if (bucket[2] -= t)
        y = 2;
    if (bucket[5] -= t)
        y = 5;

    t = min(bucket[3], bucket[4]);
    ans += t;
    if (bucket[3] -= t)
        z = 3;
    if (bucket[4] -= t)
        z = 4;

    // DP part;
    // preprocess the status;
    int stot = 0;
    for (int i = 0; i <= 7; i++)
        for (int j = 0; j <= 7; j++)
            for (int k = 0; k <= 7; k++)
                if ((i + j + k) && (i * x + j * y + k * z) % 7 == 0)
                {
                    stats[stot][0] = i, stats[stot][1] = j;
                    stats[stot][2] = k, stats[stot++][3] = i + j + k - 1;
                }
    x = bucket[x], y = bucket[y], z = bucket[z];
    for (int i = x; i >= 0; i--)
        for (int j = y; j >= 0; j--)
            for (int k = z; k >= 0; k--)
                if (x + y + z - i - j - k)
                {
                    short tmp = 0x3f3f;
                    for (int sid = 0; sid < stot; sid++)
                        if (i + stats[sid][0] <= x && j + stats[sid][1] <= y && k + stats[sid][2] <= z)
                            tmp = min(tmp, (short)(dp[i + stats[sid][0]][j + stats[sid][1]][k + stats[sid][2]] + stats[sid][3]));
                    dp[i][j][k] = tmp;
                }
    printf("%d", ans + dp[0][0][0]);
    return 0;
}