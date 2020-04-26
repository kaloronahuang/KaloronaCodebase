// C.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200;

int T, a, b, q; // pre[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &a, &b, &q);
        ll d = __gcd(a, b), lcm = 1LL * a * b / d;
        vector<int> elements;
        for (int i = 0; i < lcm; i++)
        {
            int x = i % a, y = i % b;
            if (x % b == y % a)
                elements.push_back(i);
        }
        while (q--)
        {
            ll l, r, ans = 0;
            scanf("%lld%lld", &l, &r);
            for (int i : elements)
                ans += (max(r - i, 0LL) / lcm + (i <= r)) - (max(0LL, l - i - 1) / lcm + (i <= l - 1));
            printf("%lld ", r - l + 1 - ans);
        }
        puts("");
    }
    return 0;
}