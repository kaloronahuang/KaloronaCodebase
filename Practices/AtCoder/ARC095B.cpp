// ARC095B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n;
pair<int, int> ai[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i].first), ai[i].second = ai[i].first;
    sort(ai + 1, ai + 1 + n);
    for (int i = 1;i < n; i++)
        if (ai[i].first > (ai[n].first >> 1))
            ai[i].first = ai[n].first - ai[i].first;
    sort(ai + 1, ai + 1 + n);
    printf("%d %d\n", ai[n].second, ai[n - 1].second);
    return 0;
}