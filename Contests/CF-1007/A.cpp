// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, ai[MAX_N];

int main()
{
    scanf("%d", &n);
    priority_queue<int> pq;
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), pq.push(ai[i]);
    sort(ai + 1, ai + 1 + n), reverse(ai + 1, ai + 1 + n);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        while (!pq.empty() && ai[i] <= pq.top())
            pq.pop();
        if (pq.empty())
            break;
        else
            ans++, pq.pop();
    }
    printf("%d\n", ans);
    return 0;
}