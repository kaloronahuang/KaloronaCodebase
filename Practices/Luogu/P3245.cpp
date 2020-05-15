// P3245.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n, p, suf[MAX_N], q, block;
char str[MAX_N];

namespace Subtask1
{

struct queryInfo
{
    int l, r, id;
    bool operator<(const queryInfo &rhs) const { return int(l / block) < int(rhs.l / block) || (int(l / block) == int(rhs.l / block) && r < rhs.r); }
} queries[MAX_N];

vector<int> mpping;
ll curt, ansBox[MAX_N], mp[MAX_N];

void add(int pos)
{
    curt -= mp[pos] * (mp[pos] - 1) / 2;
    mp[pos]++;
    curt += mp[pos] * (mp[pos] - 1) / 2;
}

void remove(int pos)
{
    curt -= mp[pos] * (mp[pos] - 1) / 2;
    mp[pos]--;
    curt += mp[pos] * (mp[pos] - 1) / 2;
}

int handler()
{
    for (int i = 1; i <= q; i++)
        scanf("%d%d", &queries[i].l, &queries[i].r), queries[i].r++, queries[i].id = i;
    block = sqrt(q), sort(queries + 1, queries + 1 + q);
    int cl = 1, cr = 0;
    for (int i = 0; i <= n + 1; i++)
        mpping.push_back(suf[i]);
    sort(mpping.begin(), mpping.end()), mpping.erase(unique(mpping.begin(), mpping.end()), mpping.end());
    for (int i = 0; i <= n + 1; i++)
        suf[i] = lower_bound(mpping.begin(), mpping.end(), suf[i]) - mpping.begin() + 1;
    for (int i = 1; i <= q; i++)
    {
        while (cl < queries[i].l)
            remove(suf[cl++]);
        while (cl > queries[i].l)
            add(suf[--cl]);
        while (cr < queries[i].r)
            add(suf[++cr]);
        while (cr > queries[i].r)
            remove(suf[cr--]);
        ansBox[queries[i].id] = curt;
    }
    for (int i = 1; i <= q; i++)
        printf("%lld\n", ansBox[i]);
    return 0;
}

} // namespace Subtask1

namespace Subtask2
{

int digits[10];
ll pre[MAX_N], pre_pos[MAX_N];

int handler()
{
    if (__gcd(p, 10) == 2)
        digits[0] = digits[2] = digits[4] = digits[6] = digits[8] = 1;
    else
        digits[0] = digits[5] = 1;
    for (int i = 1; i <= n; i++)
    {
        pre[i] = pre[i - 1] + digits[str[i] - '0'];
        pre_pos[i] = pre_pos[i - 1] + digits[str[i] - '0'] * i;
    }
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%lld\n", pre_pos[r] - pre_pos[l - 1] - (pre[r] - pre[l - 1]) * (l - 1));
    }
    return 0;
}

} // namespace Subtask2

int main()
{
    scanf("%d%s%d", &p, str + 1, &q), n = strlen(str + 1);
    for (int i = n, bas = 1; i >= 1; i--, bas = 10LL * bas % p)
        suf[i] = (1LL * suf[i + 1] + 1LL * bas * (str[i] - '0') % p) % p;
    int d = __gcd(p, 10);
    if (d == 1)
        return Subtask1::handler();
    else
        return Subtask2::handler();
    return 0;
}