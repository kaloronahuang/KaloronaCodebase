// P2827.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 7e6 + 200;

int n, m, q, u, v, t, seq[int(1e5) + 200];
queue<int> q1, q2, q3;
int queryans[MAX_N], acc;

int main()
{
    scanf("%d%d%d%d%d%d", &n, &m, &q, &u, &v, &t);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    sort(seq + 1, seq + 1 + n), reverse(seq + 1, seq + 1 + n);
    for (int i = 1; i <= n; i++)
        q1.push(seq[i]);
    for (int tick = 1; tick <= m; tick++)
    {
        // get the biggest;
        queue<int> *ptr = NULL;
        int val = -0x3f3f3f3f;
        if (!q1.empty() && q1.front() >= val)
            ptr = &q1, val = q1.front();
        if (!q2.empty() && q2.front() >= val)
            ptr = &q2, val = q2.front();
        if (!q3.empty() && q3.front() >= val)
            ptr = &q3, val = q3.front();
        ptr->pop();
        // split it;
        val += acc, queryans[tick] = val;
        int lft = 1LL * val * u / v, rig = val - lft;
        acc += q;
        q2.push(lft - acc), q3.push(rig - acc);
    }
    for (int i = t; i <= m; i += t)
        printf("%d ", queryans[i]);
    puts("");
    int cnt = 1;
    while (!(q1.empty() && q2.empty() && q3.empty()) && cnt <= n + m)
    {
        queue<int> *ptr = NULL;
        int val = -0x3f3f3f3f;
        if (!q1.empty() && q1.front() >= val)
            ptr = &q1, val = q1.front();
        if (!q2.empty() && q2.front() >= val)
            ptr = &q2, val = q2.front();
        if (!q3.empty() && q3.front() >= val)
            ptr = &q3, val = q3.front();
        ptr->pop();
        if (cnt % t == 0)
            printf("%d ", val + acc);
        cnt++;
    }
    return 0;
}