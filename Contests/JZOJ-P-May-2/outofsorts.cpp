// outofsorts.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, pi[MAX_N];
long long work_counter;
pair<int, int> ai[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i].first), ai[i].second = i;
    sort(ai + 1, ai + 1 + n);
    for (int i = 1; i <= n; i++)
        ai[i].first = i, swap(ai[i].first, ai[i].second);
    sort(ai + 1, ai + 1 + n);
    for (int i = n, ptr = n; i >= 1; i--)
    {
        while (ai[ptr].second > i)
            ptr--;
        pi[i] = max(ai[ptr].first - i, 1);
    }
    for (int i = 0; i < n; i++)
        work_counter += max(pi[i], pi[i + 1]);
    printf("%lld\n", work_counter);
    return 0;
}