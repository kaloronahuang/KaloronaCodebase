// P2668.cpp
#include <bits/stdc++.h>

using namespace std;

int T, n, cnt[30], ans;

void dfs(int times)
{
    // branch cut;
    if (times >= ans)
        return;
#pragma region Batch
    int k = 0;
    for (int i = 3; i <= 14; i++)
        if (cnt[i] == 0)
            k = 0;
        else
        {
            k++;
            if (k >= 5)
            {
                // opt;
                for (int j = i; j >= i - k + 1; j--)
                    cnt[j]--;
                dfs(times + 1);
                for (int j = i; j >= i - k + 1; j--)
                    cnt[j]++;
            }
        }
    k = 0;
    for (int i = 3; i <= 14; i++)
        if (cnt[i] <= 1)
            k = 0;
        else
        {
            k++;
            if (k >= 3)
            {
                // opt;
                for (int j = i; j >= i - k + 1; j--)
                    cnt[j] -= 2;
                dfs(times + 1);
                for (int j = i; j >= i - k + 1; j--)
                    cnt[j] += 2;
            }
        }
    k = 0;
    for (int i = 3; i <= 14; i++)
        if (cnt[i] <= 2)
            k = 0;
        else
        {
            k++;
            if (k >= 2)
            {
                // opt;
                for (int j = i; j >= i - k + 1; j--)
                    cnt[j] -= 3;
                dfs(times + 1);
                for (int j = i; j >= i - k + 1; j--)
                    cnt[j] += 3;
            }
        }
#pragma endregion
    for (int i = 2; i <= 14; i++)
    {
        if (cnt[i] >= 3)
        {
            cnt[i] -= 3;

            for (int j = 2; j <= 15; j++)
                if (i != j && cnt[j] > 0)
                    cnt[j]--, dfs(times + 1), cnt[j]++;

            for (int j = 2; j <= 14; j++)
                if (i != j && cnt[j] > 1)
                    cnt[j] -= 2, dfs(times + 1), cnt[j] += 2;

            cnt[i] += 3;

            if (cnt[i] >= 4)
            {
                cnt[i] -= 4;

                for (int j = 2; j <= 15; j++)
                    if (cnt[j] > 0 && i != j)
                    {
                        cnt[j]--;
                        for (int h = 2; h <= 15; h++)
                            if (cnt[h] > 0 && j != h)
                                cnt[h]--, dfs(times + 1), cnt[h]++;
                        cnt[j]++;
                    }

                for (int j = 2; j <= 14; j++)
                    if (cnt[j] > 1 && i != j)
                    {
                        cnt[j] -= 2;
                        for (int h = 2; h <= 14; h++)
                            if (cnt[h] > 1 && j != h)
                                cnt[h] -= 2, dfs(times + 1), cnt[h] += 2;
                        cnt[j] += 2;
                    }

                cnt[i] += 4;
            }
        }
    }
    for (int i = 2; i <= 15; i++)
        if (cnt[i] > 0)
            times++;
    ans = min(ans, times);
}

int main()
{
    scanf("%d%d", &T, &n);
    while (T--)
    {
        memset(cnt, 0, sizeof(cnt)), ans = 0x7f7f7f7f;
        for (int i = 1, x, y; i <= n; i++)
        {
            scanf("%d%d", &x, &y);
            if (x == 0)
                cnt[15]++;
            else if (x == 1) // A situation;
                cnt[14]++;
            else
                cnt[x]++;
        }
        dfs(0), printf("%d\n", ans);
    }
    return 0;
}