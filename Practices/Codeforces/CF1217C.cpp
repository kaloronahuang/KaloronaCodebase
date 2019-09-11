// CF1217C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, T, nxt[MAX_N];
char opt[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        int ans = 0;
        scanf("%s", opt);
        n = strlen(opt);
        for (int i = 0; i < n; i++)
            if (opt[i] == '1')
                nxt[i] = i;
            else
                nxt[i] = (i == 0 ? -1 : nxt[i - 1]);
        for (int r = 0; r < n; r++)
        {
            int number = 0;
            for (int l = r; l >= 0 && r - l < 20; l--)
            {
                if (opt[l] == '0')
                    continue;
                number |= 1 << (r - l);
                if (number <= r - (l == 0 ? -1 : nxt[l - 1]))
                    ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}