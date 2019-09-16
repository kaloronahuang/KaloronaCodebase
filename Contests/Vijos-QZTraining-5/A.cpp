// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e7 + 2;

struct vec
{
    ll x, y;
    vec operator+(const vec &target) const { return vec{x + target.x, y + target.y}; }
    vec operator*(const ll &it) const { return vec{x * it, y * it}; }
} prefix[MAX_N], up{0, 1}, down{0, -1}, rig{1, 0}, lft{-1, 0};

char opt[MAX_N];
int n, T;

int main()
{
    scanf("%s", opt + 1), n = strlen(opt + 1);
    prefix[0] = vec{0, 0};
    for (int i = 1; i <= n; i++)
        if (opt[i] == 'S')
            prefix[i] = prefix[i - 1] + down;
        else if (opt[i] == 'W')
            prefix[i] = prefix[i - 1] + lft;
        else if (opt[i] == 'E')
            prefix[i] = prefix[i - 1] + rig;
        else
            prefix[i] = prefix[i - 1] + up;
    scanf("%d", &T);
    ll rate = T / n;
    vec res = prefix[n] * rate + prefix[(T % n)];
    printf("%lld %lld", res.x, res.y);
    return 0;
}