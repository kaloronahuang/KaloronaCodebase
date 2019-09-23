// perfect.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

struct point
{
    int x, pos;
} pts[MAX_N];

int n, k, seq[MAX_N], poses[MAX_N];

int main()
{
    freopen("perfect.in", "r", stdin);
    freopen("perfect.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), poses[seq[i]] = i;
    if (k == 1 && n > 1000)
    {
        sort(seq + 1, seq + 1 + n);
        for (int i = 1; i <= n; i++)
            printf("%d\n", seq[i]);
        return 0;
    }
    if (k == n - 1)
    {
        if (abs(seq[1] - seq[n]) == 1 && seq[1] > seq[n])
            swap(seq[1], seq[n]);
        for (int i = 1; i <= n; i++)
            printf("%d\n", seq[i]);
        return 0;
    }
    for (int tim = 1; tim <= n; tim++)
        for (int i = 1; i <= n; i++)
        {
            int pos = poses[seq[i] - 1];
            if (pos == 0)
                continue;
            if (pos - i < k)
                continue;
            swap(poses[seq[pos]], poses[seq[i]]);
            swap(seq[i], seq[pos]);
        }
    for (int i = 1; i <= n; i++)
        printf("%d\n", seq[i]);
    return 0;
}