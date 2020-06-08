// P3179.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, T, block, ai[MAX_N], sg[2][MAX_N], ri[MAX_N], rtot, mark[MAX_N];

int getSg(int x) { return x <= block ? sg[0][x] : sg[1][n / x]; }

void init()
{
    for (int i = 1, j; i <= n; i = j + 1)
        j = n / (n / i), ri[++rtot] = j;
    rtot++;
    while (--rtot)
    {
        int r = ri[rtot], psg = 0, rsg = 1;
        mark[psg] = rtot;
        for (int i = (r << 1), gx; i <= n; i = gx + r)
        {
            gx = ((n / (n / i)) / r) * r, mark[psg ^ getSg(gx)] = rtot;
            if (((gx - i) / r & 1) ^ 1)
                psg ^= getSg(gx);
        }
        while (mark[rsg] == rtot)
            rsg++;
        (r <= block ? sg[0][r] : sg[1][n / r]) = rsg;
    }
}

int main()
{
    scanf("%d%d", &n, &T);
    block = sqrt(n), init();
    while (T--)
    {
        int tot = 0, ans = 0;
        scanf("%d", &tot);
        for (int i = 1; i <= tot; i++)
            scanf("%d", &ai[i]), ans ^= getSg(ai[i]);
        puts(ans ? "Yes" : "No");
    }
    return 0;
}