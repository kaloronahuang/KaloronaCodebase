// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 40;

int m, n;
bool tag[MAX_N];

void query(int x) { printf("%d\n", x), fflush(stdout); }

int main()
{
    scanf("%d%d", &m, &n);
    for (int i = 1, x; i <= n; i++)
    {
        query(m), scanf("%d", &x);
        if (x == 0)
            return 0;
        tag[i] = x == -1;
    }
    int cnt = 1, l = 1, r = m;
    while (l <= r)
    {
        int mid = (l + r) >> 1, verdict;
        query(mid), scanf("%d", &verdict);
        if (!tag[cnt])
            verdict = -verdict;
        cnt = cnt % n + 1;
        if (verdict == 0)
            return 0;
        if (verdict == 1)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return 0;
}