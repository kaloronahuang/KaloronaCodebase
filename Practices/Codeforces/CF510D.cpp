// CF510D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330;

int li[MAX_N], ci[MAX_N], n;
map<int, int> ump;
map<int, int>::iterator it;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &li[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ci[i]);
    for (int i = 1; i <= n; i++)
    {
        int tmp = ump[li[i]];
        if (tmp == 0)
            ump[li[i]] = ci[i];
        else
            ump[li[i]] = min(tmp, ci[i]);
        for (it = ump.begin(); it != ump.end(); it++)
        {
            int di = gcd(it->first, li[i]);
            tmp = ump[di];
            if (tmp == 0)
                ump[di] = it->second + ci[i];
            else
                ump[di] = min(tmp, ci[i] + it->second);
        }
    }
    printf("%d", ump[1] ? ump[1] : -1);
    return 0;
}