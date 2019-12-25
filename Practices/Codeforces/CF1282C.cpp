// CF1282C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e5 + 200;

ll m, n, T, a, b;

struct task
{
    ll typ, ti;
    bool operator<(const task &rhs) const { return ti < rhs.ti; }
} tasks[MAX_N << 1];

int main()
{
    scanf("%lld", &m);
    while (m--)
    {
        scanf("%lld%lld%lld%lld", &n, &T, &a, &b);
        ll eTot = 0, hTot = 0;
        for (int i = 1; i <= n; i++)
            scanf("%lld", &tasks[i].typ), eTot += 1 - tasks[i].typ, hTot += tasks[i].typ;
        for (int i = 1; i <= n; i++)
            scanf("%lld", &tasks[i].ti);
        sort(tasks + 1, tasks + 1 + n);
        ll cnt0 = 0, cnt1 = 0;
        tasks[++n] = task{0, T + 1};
        ll gans = 0;
        for (int ptr = 1, gx = 1; ptr <= n; ptr = gx + 1)
        {
            gx = ptr;
            ll deadline = tasks[ptr].ti - 1, pans = 0;
            ll time_mandatory = cnt0 * a + cnt1 * b;
            if (time_mandatory <= deadline)
            {
                deadline -= time_mandatory, pans += cnt0 + cnt1;
                pans += min(deadline / a, eTot - cnt0);
                deadline -= min(deadline / a, eTot - cnt0) * a;
                pans += min(deadline / b, hTot - cnt1);
                deadline -= min(deadline / b, hTot - cnt1) * b;
            }
            cnt0 += (1 - tasks[ptr].typ), cnt1 += tasks[ptr].typ;
            while (gx <= n && tasks[gx].ti == tasks[gx + 1].ti)
                gx++, cnt0 += (1 - tasks[gx].typ), cnt1 += tasks[gx].typ;
            gans = max(gans, pans);
        }
        printf("%lld\n", gans);
    }
    return 0;
}