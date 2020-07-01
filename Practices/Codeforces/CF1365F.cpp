// CF1365F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550;

int T, n, ai[MAX_N], bi[MAX_N];
bool spotted[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n), memset(spotted, false, sizeof(spotted));
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        for (int i = 1; i <= n; i++)
            scanf("%d", &bi[i]);
        int l = 1, r = n;
        bool ans = true;
        while (l < r)
        {
            bool pans = false;
            for (int i = 1; i <= n; i++)
                if (ai[l] == bi[i] && ai[r] == bi[n - i + 1] && !spotted[i] && !spotted[n - i + 1])
                {
                    spotted[i] = spotted[n - i + 1] = pans = true;
                    break;
                }
            ans &= pans;
            if (!ans)
                break;
            l++, r--;
        }
        ans &= (n % 2 == 0 || (bi[(n + 1) >> 1] == ai[(n + 1) >> 1]));
        puts(ans ? "YES" : "NO");
    }
    return 0;
}