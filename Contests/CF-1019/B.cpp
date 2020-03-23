// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

int n, ai[MAX_N];

int query(int x)
{
    if (ai[x] != INF)
        return ai[x];
    printf("? %d\n", x), fflush(stdout), scanf("%d", &ai[x]);
    return ai[x];
}

int opposite(int x) { return (x + (n >> 1) - 1) % n + 1; }

int validiate(int c)
{
    int x = query(c), y = query(opposite(c));
    if (x == y)
        printf("! %d\n", c), fflush(stdout), exit(0);
    return x > y ? 1 : -1;
}

int main()
{
    memset(ai, 0x3f, sizeof(ai));
    scanf("%d", &n);
    if (n % 4 != 0)
        puts("! -1"), fflush(stdout), exit(0);
    int l = 1, r = (n >> 1) + 1, curt = validiate(1), curt_op = -curt;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        int verdict = validiate(mid);
        if (curt * verdict < 0)
            r = mid - 1, curt_op = verdict;
        else if (curt_op * verdict < 0)
            l = mid + 1, curt = verdict;
    }
    printf("! -1\n"), fflush(stdout);
    return 0;
}