// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int T, n, c, seq[MAX_N], diff[MAX_N];
vector<int> ripe;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &c), ripe.clear();
        bool one = false;
        for (int i = 1; i <= n; i++)
            scanf("%d", &seq[i]), ripe.push_back(seq[i]), one |= (seq[i] == 1);
        for (int i = 1; i <= c; i++)
            diff[i] = 0;
        if (!one)
        {
            puts("No");
            continue;
        }
        sort(ripe.begin(), ripe.end()), ripe.erase(unique(ripe.begin(), ripe.end()), ripe.end());
        for (int i = 0, siz = ripe.size(); i < siz; i++)
            for (int j = 0; j < siz && 1LL * ripe[i] * ripe[j] <= c; j++)
            {
                int b = ripe[i], y = ripe[j];
                int rangel = 1LL * b * y, ranger = min(1LL * c, 1LL * b * y + y - 1);
                diff[rangel]++, diff[ranger + 1]--;
            }
        for (int i = 1; i <= c; i++)
            diff[i] += diff[i - 1];
        bool gans = true;
        for (int i = 0, siz = ripe.size(); i < siz; i++)
            gans &= (diff[ripe[i]] == i + 1);
        puts(gans ? "Yes" : "No");
    }
    return 0;
}