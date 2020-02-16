// CF1301D.cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, k;

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    if (4LL * n * m - 2LL * n - 2LL * m < k)
        puts("NO"), exit(0);
    else
        puts("YES");
    vector<pair<string, int> /**/> ans;
    // the first row;
    if (m > 1)
    {
        ans.push_back(make_pair("R", min(m - 1, k)));
        k -= min(k, m - 1);
        if (k == 0)
            goto CalcPhase;
    }
    if (m > 1)
    {
        ans.push_back(make_pair("L", min(m - 1, k)));
        k -= min(k, m - 1);
        if (k == 0)
            goto CalcPhase;
    }
    if (n > 1)
    {
        ans.push_back(make_pair("D", min(1, k)));
        k -= min(1, k);
        if (k == 0)
            goto CalcPhase;
    }
    for (int i = 2; i < n; i++)
    {
        if (m > 1)
        {
            ans.push_back(make_pair("R", min(m - 1, k)));
            k -= min(k, m - 1);
            if (k == 0)
                goto CalcPhase;
        }
        if (m > 1)
        {
            if (k < 3 * (m - 1))
            {
                int lp = (k / 3), rem = k % 3;
                if (lp > 0)
                    ans.push_back(make_pair("UDL", lp));
                if (rem)
                    ans.push_back(make_pair("U", 1)), rem--;
                if (rem)
                    ans.push_back(make_pair("D", 1)), rem--;
            }
            else
                ans.push_back(make_pair("UDL", min(m - 1, k)));
            k -= min(k, 3 * (m - 1));
            if (k == 0)
                goto CalcPhase;
        }
        ans.push_back(make_pair("D", min(1, k)));
        k -= min(1, k);
        if (k == 0)
            goto CalcPhase;
    }
    // last row;
    if (n >= 2)
    {
        if (m > 1)
        {
            ans.push_back(make_pair("R", min(k, m - 1)));
            k -= min(k, m - 1);
            if (k == 0)
                goto CalcPhase;
        }
        if (m > 1)
        {
            if (k < 3 * (m - 1))
            {
                int lp = (k / 3), rem = k % 3;
                if (lp > 0)
                    ans.push_back(make_pair("UDL", lp));
                if (rem)
                    ans.push_back(make_pair("U", 1)), rem--;
                if (rem)
                    ans.push_back(make_pair("D", 1)), rem--;
            }
            else
                ans.push_back(make_pair("UDL", min(m - 1, k)));
            k -= min(k, 3 * (m - 1));
            if (k == 0)
                goto CalcPhase;
        }
        ans.push_back(make_pair("U", min(k, n - 1)));
        k = 0;
    }
CalcPhase:
    printf("%d\n", ans.size());
    for (int i = 0, siz = ans.size(); i < siz; i++)
        cout << ans[i].second << " " << ans[i].first << endl;
    return 0;
}