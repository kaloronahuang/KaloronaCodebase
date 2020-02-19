// CF1307E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 1e9 + 7;

int n, m, si[MAX_N], fi[MAX_N], hi[MAX_N], max_capacity[MAX_N];
int pre_bucket[MAX_N], suf_bucket[MAX_N];
vector<int> cows[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &si[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &fi[i], &hi[i]), cows[fi[i]].push_back(hi[i]);
    int gans = 0, sol = 0;
    for (int i = 1; i <= n; i++)
        sort(cows[i].begin(), cows[i].end());
    for (int pos = 0; pos <= n; pos++)
    {
        memset(pre_bucket, 0, sizeof(pre_bucket));
        memset(suf_bucket, 0, sizeof(suf_bucket));
        for (int i = 1; i <= pos; i++)
            pre_bucket[si[i]]++;
        for (int i = pos + 1; i <= n; i++)
            suf_bucket[si[i]]++;

        bool flag = (pos == 0);
        for (int i = 0, siz = cows[si[pos]].size(); i < siz; i++)
            if (cows[si[pos]][i] == pre_bucket[si[pos]])
            {
                flag = true;
                break;
            }
        if (!flag)
            continue;
        int psol = 1, pans = (pos != 0);
        for (int i = 1; i <= n; i++)
        {
            int siz = cows[i].size(), lptr = 0, rptr = 0;
            while (lptr < siz && cows[i][lptr] <= pre_bucket[i])
                lptr++;
            while (rptr < siz && cows[i][rptr] <= suf_bucket[i])
                rptr++;
            if (i == si[pos])
                lptr = 0, rptr -= (suf_bucket[i] >= pre_bucket[i]);
            if (lptr > rptr)
                swap(lptr, rptr);
            if (lptr == 0 && rptr == 0)
                continue;
            else if (lptr == 0)
                psol = 1LL * psol * rptr % mod, pans++;
            else if (rptr > 1)
                psol = 1LL * psol * lptr % mod * (rptr - 1) % mod, pans += 2;
            else
                psol = 2LL * psol % mod, pans++;
        }
        if (pans == gans)
            sol = (0LL + sol + psol) % mod;
        if (pans > gans)
            gans = pans, sol = psol;
    }
    printf("%d %d\n", gans, sol);
    return 0;
}