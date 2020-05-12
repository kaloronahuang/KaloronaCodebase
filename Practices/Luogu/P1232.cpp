// P1232.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, dseq[MAX_N], pos[MAX_N], diff[MAX_N];

void mark(int l, int r) { diff[l]++, diff[r + 1]--; }

int main()
{
    scanf("%d", &n);
    for (int i = 1, id; i <= n; i++)
        scanf("%d", &id), dseq[id] = i;
    for (int i = 1, id; i <= n; i++)
        scanf("%d", &id), pos[dseq[id]] = i;
    for (int i = 1; i <= n; i++)
        dseq[pos[i]] = i;
    double ans = 0;
    for (int i = 1; i < n; i++)
    {
        if (dseq[i] > dseq[i + 1])
            mark(i, i), ans++;
        if (pos[i] < pos[i + 1] - 1)
            mark(pos[i], pos[i + 1] - 1);
    }
    int curt = 0;
    for (int i = 1; i <= n; i++)
        curt += diff[i], ans += (curt > 0 ? 0 : 0.5);
    ans++, printf("%.3lf\n", ans);
    return 0;
}