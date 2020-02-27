// CF1190B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, ai[MAX_N];
ll ans;

void firstWin() { puts("sjfnb"), exit(0); }

void secondWin() { puts("cslnb"), exit(0); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), ans += ai[i];
    sort(ai + 1, ai + 1 + n);
    int level_cnt = 0;
    for (int i = 1; i < n; i++)
        level_cnt += (ai[i] == ai[i + 1]);

    if (level_cnt >= 2)
        secondWin();
    if (level_cnt == 1)
        for (int i = 1; i < n; i++)
            if (ai[i] == ai[i + 1])
            {
                if (i != 1 && ai[i - 1] == ai[i] - 1)
                    secondWin();
                if (ai[i] == 0)
                    secondWin();
            }
    ans -= 1LL * n * (n - 1) / 2;
    if (ans <= 0)
        secondWin();
    if (ans & 1)
        firstWin();
    secondWin();
    return 0;
}