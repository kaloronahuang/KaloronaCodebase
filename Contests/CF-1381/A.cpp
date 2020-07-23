// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n;
char src[MAX_N], target[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%s%s", &n, src, target);
        vector<int> q1, q2;
        src[n] = target[n] = '0';
        for (int i = 1; i <= n; i++)
        {
            if (src[i] != src[i - 1])
                q1.push_back(i);
            if (target[i] != target[i - 1])
                q2.push_back(i);
        }
        q1.insert(q1.end(), q2.rbegin(), q2.rend());
        printf("%d ", int(q1.size()));
        for (int x : q1)
            printf("%d ", x);
        puts("");
    }
    return 0;
}