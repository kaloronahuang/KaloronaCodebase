// P2215.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200;

int seq[MAX_N], n, m, length[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), length[i] = 1;
    for (int i = n; i >= 1; i--)
        for (int j = i + 1; j <= n; j++)
            if (seq[i] < seq[j] && length[j] + 1 > length[i])
                length[i] = length[j] + 1;
    scanf("%d", &m);
    while (m--)
    {
        int x, pos;
        scanf("%d", &x);
        for (pos = 1; pos <= n; pos++)
            if (length[pos] >= x)
                break;
        if (pos == n + 1)
        {
            puts("Impossible");
            continue;
        }
        while (pos <= n && x > 0)
        {
            printf("%d ", seq[pos]), x--;
            for (int nxt = pos + 1; nxt <= n && x; nxt++)
                if (seq[nxt] > seq[pos] && length[nxt] >= x)
                {
                    pos = nxt;
                    break;
                }
        }
        puts("");
    }
    return 0;
}