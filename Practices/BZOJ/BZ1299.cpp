// BZ1299.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 50;

int T = 10, n, ai[MAX_N];

int main()
{
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; scanf("%d", &ai[i]), i++)
            ;
        bool flag = false;
        for (int stat = 1; stat < (1 << n) && flag == false; stat++)
        {
            int acc = 0;
            for (int i = 0; i < n; i++)
                if (stat & (1 << i))
                    acc ^= ai[i];
            if (acc == 0)
                flag = true;
        }
        puts(flag ? "NO" : "YES");
    }
    return 0;
}