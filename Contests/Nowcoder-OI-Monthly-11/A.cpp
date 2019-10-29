// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2001100;

int prefix[MAX_N][3];

int main()
{
    prefix[1][0] = 0, prefix[1][1] = 1;
    for (int i = 2; i < MAX_N; i++)
        prefix[i][0] = prefix[i - 1][1], prefix[i][1] = prefix[i - 1][0] ^ i, prefix[i][2] = prefix[i - 1][2] ^ i;
    int n, m;
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x2 - x1 >= y2 - y1)
            swap(x2, y2);
        int x = x2 - x1 + 1, y = y2 - y1 + 1;
        int a = x1 + y1 - 1, ans = prefix[a + x - 1][x & 1] ^ prefix[a - 1][0];
        if (x & 1)
            ans ^= prefix[a + y - 1][3] ^ prefix[a + x - 1][3];
        ans ^= prefix[a + y - 1][x & 1] ^ prefix[a + y + x - 2][1];
        printf("%d\n", ans);
    }
    return 0;
}