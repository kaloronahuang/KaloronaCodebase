// CF1053B.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 3e5 + 200;

int n, prefix[MAX_N];
ll ai[MAX_N], cnt[2], ans;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]), prefix[i] = prefix[i - 1] + __builtin_popcountll(ai[i]);
    cnt[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        ans += cnt[prefix[i] & 1], cnt[prefix[i] & 1]++;
        for (int j = i, ptr = j + 1, max_val = 0; j >= i - 64 && j >= 1; j--)
        {
            while (ptr > j)
                ptr--, max_val = max(max_val, prefix[ptr] - prefix[ptr - 1]);
            if (max_val * 2 > prefix[i] - prefix[j - 1] && prefix[i] % 2 == prefix[j - 1] % 2)
                ans--;
        }
    }
    printf("%lld\n", ans);
    return 0;
}