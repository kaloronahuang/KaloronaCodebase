// color.cpp
#include <bits/stdc++.h>

using namespace std;

int T, p1, p2, k;

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
}

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    fileIO("color");
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &p1, &p2, &k);
        if (p1 == p2)
        {
            puts("Yes");
            continue;
        }
        if (p1 > p2)
            swap(p1, p2);
        int d = gcd(p1, p2);
        int max_same = (p2 - d - 1) / p1 + 1;
        if (k > max_same)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}