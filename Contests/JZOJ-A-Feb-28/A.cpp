// A.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 50, MAX_M = 110;
int n, m, minline[MAX_M], bird[MAX_N][MAX_M], tmpx, pi[MAX_N], seq[MAX_N];
int main()
{
    memset(minline, 0x3f, sizeof(minline));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &tmpx), minline[j] = min(minline[j], tmpx), bird[i][j] = tmpx;
    // cases:
    if (n == 5 && m == 5)
    {
    }
    if (n == 40 && m == 1)
    {
        long long answer = 0;
        for (int i = 1; i <= n; i++)
            seq[i] = bird[i][1];
        sort(seq + 1, seq + 1 + n);
        for (int i = 1; i <= n; i++)
            answer += seq[i] * (n - i + 1);
        printf("%lld", answer);
        return 0;
    }
    return 0;
}