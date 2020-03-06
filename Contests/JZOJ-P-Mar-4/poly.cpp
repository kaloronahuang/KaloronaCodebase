// poly.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, coeff[MAX_N], tmp[MAX_N];
bool vis[MAX_N];
vector<int> vec;

inline char nc()
{
    static char buffer[1 << 20], *p1 = buffer, *p2 = buffer;
    return p1 == p2 && (p2 = (p1 = buffer) + fread(buffer, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char c = nc();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = nc();
    }
    while (isdigit(c))
        x = (x << 3) + (x << 1) + c - '0', c = nc();
    return x * f;
}

void fileIO()
{
    freopen("poly.in", "r", stdin);
    freopen("poly.out", "w", stdout);
}

bool check(int x)
{
    if (coeff[0] % x != 0)
        return false;
    for (int i = 0; i <= x; i++)
        tmp[i] = 0;
    for (int i = 0; i <= n; i++)
        tmp[i % (x - 1)] = (tmp[i % (x - 1)] + coeff[i]) % x;
    for (int i = 0; i <= x - 2; i++)
        if (tmp[i])
            return false;
    return true;
}

int main()
{
    scanf("%d", &n);
    int d = 0;
    for (int i = n; i >= 0; i--)
        scanf("%d", &coeff[i]), d = __gcd(d, coeff[i]);
    d = abs(d);
    for (int i = 2; 1LL * i * i <= d; i++)
        if (d % i == 0)
        {
            vec.push_back(i);
            while (d % i == 0)
                d /= i;
        }
    if (d > 1)
        vec.push_back(d);
    for (int i = 2; i <= n; i++)
        if (!vis[i])
        {
            if (check(i))
                vec.push_back(i);
            for (int j = (i << 1); j <= n; j += i)
                vis[j] = true;
        }
    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for (int i = 0, siz = vec.size(); i < siz; i++)
        printf("%d\n", vec[i]);
    return 0;
}