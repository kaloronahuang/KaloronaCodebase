// LOJ3154.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int n, ai[MAX_N], bi[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ai[i], &bi[i]);
    for (int T = 0; T < 30; T++)
        for (int i = 1; i <= n; i++)
            if (ai[i] > bi[i])
            {
                int diff = ((ai[i] - bi[i]) >> 1) + ((ai[i] - bi[i]) & 1);
                if (ai[i] < (diff << 1))
                    diff--;
                ai[i] -= (diff << 1), ai[i % n + 1] += diff;
            }
    for (int i = 1; i <= n; i++)
        if (ai[i] != bi[i])
            puts("No"), exit(0);
    puts("Yes");
    return 0;
}