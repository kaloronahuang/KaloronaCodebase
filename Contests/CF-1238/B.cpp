// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int q, n, r, seq[MAX_N];

int main()
{
    scanf("%d", &q);
    while (q--)
    {
        scanf("%d%d", &n, &r);
        for (int i = 1; i <= n; i++)
            scanf("%d", &seq[i]);
        sort(seq + 1, seq + 1 + n), n = unique(seq + 1, seq + 1 + n) - seq - 1;
        int cnt = 0;
        for (int i = n, bias = 0; i >= 1; i--)
        {
            int now = seq[i] - bias;
            if (now <= 0)
                break;
            bias += r, cnt++;
        }
        printf("%d\n", cnt);
    }
    return 0;
}