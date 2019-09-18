// AT141D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m;
priority_queue<long long> pq;

int main()
{
    scanf("%d%d", &n, &m);
    long long ans = 0;
    for (int i = 1, tmp; i <= n; i++)
        scanf("%d", &tmp), pq.push(tmp), ans += tmp;
    while (m--)
    {
        long long tp = pq.top();
        pq.pop();
        long long tmp = tp >> 1;
        pq.push(tmp), ans -= (tp - tmp);
    }
    printf("%lld", ans);
    return 0;
}