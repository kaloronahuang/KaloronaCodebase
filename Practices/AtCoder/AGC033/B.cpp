// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, m, len, sx, sy;
char S[MAX_N], T[MAX_N];

int main()
{
    scanf("%d%d%d%d%d%s%s", &n, &m, &len, &sx, &sy, S + 1, T + 1);
    // upper;
    bool ans = false;
    int x = sx, y = sy;
    for (int i = 1; i <= len; i++)
    {
        if (S[i] == 'U')
            x--;
        if (x < 1)
            ans = true;
        if (T[i] == 'D' && x < n)
            x++;
        if (x < 1)
            ans = true;
    }
    x = sx, y = sy;
    for (int i = 1; i <= len; i++)
    {
        if (S[i] == 'D')
            x++;
        if (x > n)
            ans = true;
        if (T[i] == 'U' && x > 1)
            x--;
        if (x > n)
            ans = true;
    }
    x = sx, y = sy;
    for (int i = 1; i <= len; i++)
    {
        if (S[i] == 'L')
            y--;
        if (y < 1)
            ans = true;
        if (T[i] == 'R' && y < m)
            y++;
        if (y < 1)
            ans = true;
    }
    x = sx, y = sy;
    for (int i = 1; i <= len; i++)
    {
        if (S[i] == 'R')
            y++;
        if (y > m)
            ans = true;
        if (T[i] == 'L' && y > 1)
            y--;
        if (y > m)
            ans = true;
    }
    puts(ans ? "NO" : "YES");
    return 0;
}