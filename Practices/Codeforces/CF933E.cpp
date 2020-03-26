// CF933E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

typedef long long ll;

int n, ai[MAX_N], pi[MAX_N];
ll f[MAX_N];
bool opt[MAX_N];
vector<int> ans;

int process(int pos)
{
    int val = min(ai[pos], ai[pos + 1]);
    if (val)
        ans.push_back(pos);
    ai[pos] -= val, ai[pos + 1] -= val;
    return val;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ai[i]);
        ll single = f[max(0, i - 2)] + ai[i], binary = f[max(0, i - 3)] + max(ai[i], ai[i - 1]);
        f[i] = min(single, binary), opt[i] = f[i] != single;
    }
    int cnt = 0;
    for (int i = min(f[n - 1], f[n]) == f[n - 1] ? n - 1 : n; i >= 1; i -= (opt[i] == true) + 2)
        pi[++cnt] = i;
    reverse(pi + 1, pi + 1 + cnt);
    for (int i = 1; i <= cnt; i++)
    {
        int pre = pi[i - 1], curt = pi[i];
        ll acc = 0;
        if (opt[curt])
            acc += process(curt - 1);
        acc += process(pre + 1), acc += process(curt);
    }
    printf("%lld\n", 1LL * ans.size());
    for (auto &x : ans)
        printf("%d\n", x);
    puts("");
    return 0;
}