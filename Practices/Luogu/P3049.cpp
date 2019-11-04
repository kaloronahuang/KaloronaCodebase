// P3049.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int n, x, y, z, ai[MAX_N], bi[MAX_N], delta[MAX_N], pre[MAX_N], ans;

priority_queue<int> pq1, pq2;

int main()
{
    scanf("%d%d%d%d", &n, &x, &y, &z);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &ai[i], &bi[i]);
        if (bi[i] >= ai[i])
            for (int j = 1; j <= bi[i] - ai[i]; j++)
                if (pq1.empty() || i * z - pq1.top() >= x)
                    ans += x, pq2.push(x + i * z);
                else
                {
                    int curt = pq1.top();
                    pq1.pop(), ans += i * z - curt, pq2.push(i * z * 2 - curt);
                }
        else
            for (int j = 1; j <= ai[i] - bi[i]; j++)
                if (pq2.empty() || i * z - pq2.top() >= y)
                    ans += y, pq1.push(y + i * z);
                else
                {
                    int curt = pq2.top();
                    pq2.pop(), ans += i * z - curt, pq1.push(i * z * 2 - curt);
                }
    }
    printf("%d", ans);
    return 0;
}
