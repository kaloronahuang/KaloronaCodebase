// lis.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n;
long long ans;
priority_queue<int> pq;

int main()
{
    scanf("%d", &n);
    int val = 0, y;
    scanf("%d", &val), pq.push(-val);
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &val), pq.push(-val), y = -pq.top();
        if (val > y)
            ans += val - y, pq.pop(), pq.push(-val);
    }
    printf("%lld\n", ans);
    return 0;
}