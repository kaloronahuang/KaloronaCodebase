// CF865D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

priority_queue<int, vector<int>, greater<int>> pq;

int n;
long long ans;

int main()
{
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++)
    {
        scanf("%d", &x), pq.push(x), pq.push(x);
        ans += 0LL + x - pq.top(), pq.pop();
    }
    printf("%lld\n", ans);
    return 0;
}