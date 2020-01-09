// FOJ3948.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 22;

int n, k, last[MAX_N], cnt;
long long subtree3[MAX_N], ans;

void solve_normal(int source, int target, int spare, int step)
{
    if (step > 0)
    {
        solve_normal(source, spare, target, step - 1);
        if (cnt <= 0)
            return;
        last[step] = target, cnt--;
        solve_normal(spare, target, source, step - 1);
    }
}

void solve_strange(int source, int target, int spare, int step)
{
    if (step > 0)
    {
        if (last[step] == source)
            return (void)(solve_strange(source, target, spare, step - 1));
        if (last[step] == spare)
            return (void)(ans += subtree3[step - 1] + 1, solve_strange(target, source, spare, step - 1));
        ans += (subtree3[step - 1] + 1) << 1;
        solve_strange(source, target, spare, step - 1);
    }
}

int main()
{
    scanf("%d%d", &n, &k), cnt = k;
    solve_normal(0, 1, 2, n);
    for (int i = 1; i <= n; i++)
        subtree3[i] = 3LL * subtree3[i - 1] + 2;
    solve_strange(0, 1, 2, n);
    printf("%lld\n", ans);
    return 0;
}