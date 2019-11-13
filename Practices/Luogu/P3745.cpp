// P3745.cpp
#include <bits/stdc++.h>
typedef unsigned long long ll;

using namespace std;

const int MAX_N = 1e5 + 200;

ll A, B, C, n, m, ti[MAX_N], bi[MAX_N], bucket[MAX_N], frame[MAX_N], prefix[MAX_N], pre[MAX_N];

int main()
{
    scanf("%lld%lld%lld%lld%lld", &A, &B, &C, &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ti[i]);
    for (int i = 1; i <= m; i++)
        scanf("%lld", &bi[i]);
    sort(ti + 1, ti + 1 + n), sort(bi + 1, bi + 1 + m);
    ll latest_time = 0, last_p = 0;
    for (int i = 1; i <= m; i++)
        bucket[bi[i]]++, latest_time = max(latest_time, bi[i]), prefix[i] = prefix[i - 1] + bi[i];
    for (int i = 1; i <= n; i++)
    {
        frame[ti[i]]++, pre[i] = pre[i - 1] + ti[i];
        if (ti[i] <= latest_time)
            last_p = i;
    }
    ll ans = 0x7fffffffffffffff, class_in_need = 0;
    for (int tim = latest_time; tim >= 1; tim--)
    {
        last_p -= frame[tim];
        ll tmp = 0;
        if (A >= B)
            // use B instead;
            tmp = max(B * (prefix[m] - prefix[m - class_in_need] - class_in_need * tim), (ll)(0));
        else
        {
            ll Bday = prefix[m] - prefix[m - class_in_need] - class_in_need * tim;
            ll Aday = (m - class_in_need) * tim - prefix[m - class_in_need];
            if (Bday <= Aday)
                tmp = max(Bday * A, (ll)0);
            else
                tmp = max((Bday - Aday) * B + Aday * A, (ll)(0));
        }
        tmp += max(last_p * tim - pre[last_p], (ll)(0)) * C;
        class_in_need += bucket[tim], ans = min(ans, tmp);
    }
    printf("%lld", ans);
    return 0;
}