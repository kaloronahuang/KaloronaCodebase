// CF1179B.cpp
#include <bits/stdc++.h>

using namespace std;

void solve(int n, int m)
{
    if (n == 2 && m == 3)
        return (void)(printf("1 1\n1 3\n1 2\n2 2\n2 3\n2 1"));
    for (int i = 1; i <= (n >> 1); i++)
        for (int j = 1; j <= m; j++)
            printf("%d %d\n", i, j), printf("%d %d\n", n - i + 1, m - j + 1);
    if (n & 1)
    {
        int x = (n >> 1);
        deque<int> acc;
        printf("%d %d\n", x + 1, 1);
        for (int i = 1; i < m; i++)
            acc.push_back(i);
        while (!acc.empty())
        {
            printf("%d %d\n", x + 1, acc.back() + 1), acc.pop_back();
            if (!acc.empty())
                printf("%d %d\n", x + 1, acc.front() + 1), acc.pop_front();
        }
    }
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m), solve(n, m);
    return 0;
}