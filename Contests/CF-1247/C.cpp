// C.cpp
#include <bits/stdc++.h>
using namespace std;

long long n, p, tot, nbas = 1 << 30;

bool dfs(int now, int depth, int base)
{
    bool tmp = 0;
    if (depth == 0 && now == 0)
        return 1;
    if (depth == 0 && now != 0)
        return 0;
    while (now < base)
        base >>= 1;
    if (dfs(now - base, depth - 1, base))
        tmp = 1;
    return tmp;
}

int main()
{
    scanf("%lld%lld", &n, &p);
    int temp = n, imax = log2(n) + 5;
    for (int i = 1; i <= imax; i++)
    {
        n = temp - i * p;
        if (n <= 0)
            continue;
        if (dfs(n, i, nbas))
            printf("%d\n", i), exit(0);
    }
    puts("-1");
    return 0;
}