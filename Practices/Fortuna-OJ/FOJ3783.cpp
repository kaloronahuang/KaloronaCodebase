// FOJ3783.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, ai[MAX_N], prefix[MAX_N], last_pos[MAX_N];

void fileIO()
{
    freopen("checkin.in", "r", stdin);
    freopen("checkin.out", "w", stdout);
}

int main()
{
    fileIO();
    scanf("%d", &T);
    while (T--)
    {
        memset(last_pos, -1, sizeof(last_pos)), last_pos[0] = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        for (int i = 1; i <= n; i++)
        {
            prefix[i] = (prefix[i - 1] + (ai[i] % n)) % n;
            while (prefix[i] < 0)
                prefix[i] += n;
            prefix[i] %= n;
            if (last_pos[prefix[i]] != -1)
            {
                printf("%d\n", i - last_pos[prefix[i]]);
                for (int j = last_pos[prefix[i]] + 1; j <= i; j++)
                    printf("%d ", ai[j]);
                puts("");
                break;
            }
            last_pos[prefix[i]] = i;
        }
    }
    return 0;
}