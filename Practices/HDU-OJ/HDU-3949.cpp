// HDU-3949.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 10100;

ll T, n, q, arr[MAX_N];

int main()
{
    scanf("%lld", &T);
    for (int tst = 1; tst <= T; tst++)
    {
        scanf("%lld", &n);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &arr[i]);
        bool zero = false;
        int t = n;
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
                if (arr[j] > arr[i])
                    swap(arr[j], arr[i]);
            if (arr[i] == 0)
            {
                zero = true, t = i - 1;
                break;
            }
            for (int bit = 63; bit >= 0; bit--)
                if ((arr[i] >> bit) & 1)
                {
                    for (int k = 1; k <= n; k++)
                        if (k != i && ((arr[k] >> bit) & 1))
                            arr[k] ^= arr[i];
                    break;
                }
        }
        scanf("%lld", &q), printf("Case #%d:\n", tst);
        while (q--)
        {
            unsigned ll k, ans = 0;
            scanf("%lld", &k);
            if (zero)
                k--;
            if (k >= (1llu << t))
                puts("-1");
            else
            {
                for (int i = t - 1; i >= 0; i--)
                    if ((k >> i) & 1)
                        ans ^= arr[t - i];
                printf("%lld\n", ans);
            }
        }
    }
    return 0;
}