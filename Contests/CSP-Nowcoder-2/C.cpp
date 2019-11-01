// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int ai[MAX_N], n, m, force;

int read()
{
    int x = 0;
    scanf("%d", &x);
    return x;
}

void subtask1()
{
    int lastans = 0;
    while (m--)
    {
        int opt, x, y, z;
        opt = read(), x = read(), y = read();
        if (force)
            x ^= lastans, y ^= lastans;
        if (opt == 1)
        {
            z = read();
            if (force)
                z ^= lastans;
            for (int i = x; i <= y; i++)
                ai[i] = z;
        }
        else
        {
            int ans = 0x3f3f3f3f;
            for (int i = 1, xpos = -1, ypos = -1; i <= n; i++)
            {
                if (ai[i] == x)
                    xpos = i;
                else if (ai[i] == y)
                    ypos = i;
                if (xpos != -1 && ypos != -1)
                    ans = min(ans, abs(xpos - ypos));
            }
            if (ans == 0x3f3f3f3f)
                puts("-1"), lastans = 0;
            else
                printf("%d\n", ans), lastans = ans;
        }
    }
}

int main()
{
    n = read(), m = read(), force = read();
    for (int i = 1; i <= n; i++)
        ai[i] = read();
    subtask1();
    return 0;
}