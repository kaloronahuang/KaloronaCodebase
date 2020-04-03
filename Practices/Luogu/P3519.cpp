// P3519.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200;

typedef pair<int, int> pii;

int n;
char str[MAX_N];
vector<int> pos[26];

int main()
{
    scanf("%d%s", &n, str + 1);
    for (int i = 1; i <= n; i++)
        pos[str[i] - 'a'].push_back(i);
    int ans = 0;
    for (int ca = 0; ca < 26; ca++)
        if (!pos[ca].empty())
            for (int cb = 0; cb < 26; cb++)
                if (!pos[cb].empty() && ca != cb)
                {
                    int curt_a = 0, curt_b = 0;
                    int aptr = 0, bptr = 0, siza = pos[ca].size(), sizb = pos[cb].size();
                    deque<pii> qmin;
                    qmin.push_back(make_pair(0, 0));
                    while (aptr < siza && bptr < sizb)
                    {
                        if (pos[ca][aptr] < pos[cb][bptr])
                            aptr++, curt_a++;
                        else
                            bptr++, curt_b++;
                        if (curt_a > 0 && curt_b > 0)
                        {
                            while (qmin.size() > 1 && qmin[1].first < curt_a && qmin[1].second < curt_b)
                                qmin.pop_front();
                            if (curt_a > qmin.front().first && curt_b > qmin.front().second)
                                ans = max(ans, abs(curt_a - curt_b - (qmin.front().first - qmin.front().second)));
                        }
                        if (curt_a - curt_b < qmin.back().first - qmin.back().second)
                            qmin.push_back(make_pair(curt_a, curt_b));
                    }
                    while (aptr < siza)
                    {
                        aptr++, curt_a++;
                        if (curt_a > 0 && curt_b > 0)
                        {
                            while (qmin.size() > 1 && qmin[1].first < curt_a && qmin[1].second < curt_b)
                                qmin.pop_front();
                            if (curt_a > qmin.front().first && curt_b > qmin.front().second)
                                ans = max(ans, abs(curt_a - curt_b - (qmin.front().first - qmin.front().second)));
                        }
                        if (curt_a - curt_b < qmin.back().first - qmin.back().second)
                            qmin.push_back(make_pair(curt_a, curt_b));
                    }
                    while (bptr < sizb)
                    {
                        bptr++, curt_b++;
                        if (curt_a > 0 && curt_b > 0)
                        {
                            while (qmin.size() > 1 && qmin[1].first < curt_a && qmin[1].second < curt_b)
                                qmin.pop_front();
                            if (curt_a > qmin.front().first && curt_b > qmin.front().second)
                                ans = max(ans, abs(curt_a - curt_b - (qmin.front().first - qmin.front().second)));
                        }
                        if (curt_a - curt_b < qmin.back().first - qmin.back().second)
                            qmin.push_back(make_pair(curt_a, curt_b));
                    }
                }
    printf("%d\n", ans);
    return 0;
}