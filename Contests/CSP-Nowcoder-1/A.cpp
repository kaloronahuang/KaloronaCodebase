// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e3 + 200, table[8] = {0, 0, 1, 1, 1, 1, 1, 1};

int T, n, ai[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        bool flag = false;
        for (int i = 1; i <= n; i++)
            flag ^= (ai[i] == 1);
        printf(flag ? "rabbit\n" : "hamster\n");
    }
    return 0;
}