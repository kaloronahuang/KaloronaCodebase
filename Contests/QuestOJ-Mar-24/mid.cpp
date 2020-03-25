// mid.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e7 + 200;

int n, ai[MAX_N], last_ans, ans;
priority_queue<int, vector<int>, greater<int>> pq1;
priority_queue<int> pq2;

int main()
{
    scanf("%d%d", &n, &ai[1]), last_ans = ans = ai[1], pq2.push(ai[1]);
    for (int i = 2; i <= n; i++)
    {
        ai[i] = (1714636915LL * ai[i - 1] % 1000000007 + 1681692777LL) * (846930886LL * last_ans % 1000000007 + 1804289383LL) % 1000000007;
        if (i & 1)
            if (ai[i] <= pq1.top())
                pq2.push(ai[i]);
            else
                pq2.push(pq1.top()), pq1.pop(), pq1.push(ai[i]);
        else if (ai[i] >= pq2.top())
            pq1.push(ai[i]);
        else
            pq1.push(pq2.top()), pq2.pop(), pq2.push(ai[i]);
        last_ans = pq2.top(), ans ^= pq2.top();
    }
    printf("%d\n", ans);
    return 0;
}