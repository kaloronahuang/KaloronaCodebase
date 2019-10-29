// YBT-OJ1671.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1001000;

int n, b, seq[MAX_N];

int main()
{
    priority_queue<int> pq;
    scanf("%d%d", &n, &b);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), pq.push(-seq[i]);
    int ans, all_set_num = -pq.top();
    ans = all_set_num;
    while (true)
    {
        // fill the minimum one without special cards;
        for (int i = 1; i <= all_set_num; i++)
        {
            // if there is room for sp card reducing;
            if (b == 0)
                break;
            int now = -pq.top();
            pq.pop(), pq.push(-(now + 1)), b--;
        }
        int reduced_res = -pq.top();
        if (ans == reduced_res)
            // no need for exchanging the sp cards or sth etc;
            break;
        all_set_num = reduced_res - ans;
        ans = reduced_res;
    }
    printf("%d", ans);
    return 0;
}