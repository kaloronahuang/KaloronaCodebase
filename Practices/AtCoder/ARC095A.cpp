// ARC095A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef pair<int, int> pii;

int n, ans[MAX_N];
pii seq[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i].first), seq[i].second = i;
    sort(seq + 1, seq + 1 + n);
    for (int i = 1; i <= n; i++)
    {
        int idx = n >> 1;
        if (i <= idx)
            ans[seq[i].second] = seq[idx + 1].first;
        else
            ans[seq[i].second] = seq[idx].first;
    }
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
    return 0;
}