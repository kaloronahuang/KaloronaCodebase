// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int ch[int(1e7) + 200][2], ptot = 1, prefix[MAX_N], n, seq[MAX_N];

void insert(int x)
{
    int p = 1;
    for (int i = 30; i >= 0; i--)
    {
        int bit = (x >> i) & 1;
        if (ch[p][bit] == 0)
            ch[p][bit] = ++ptot, ch[ptot][0] = ch[ptot][1] = 0;
        p = ch[p][bit];
    }
}

int query(int x)
{
    int p = 1, sum = 0;
    for (int i = 30; i >= 0; i--)
    {
        int bit = (x >> i) & 1;
        if (ch[p][bit ^ 1] != 0)
            p = ch[p][bit ^ 1], sum ^= (1 << i);
        else
            p = ch[p][bit];
    }
    return sum;
}

void reset() { ptot = 1, ch[1][0] = ch[1][1] = 0; }

int solve(int l, int r)
{
    if (l == r)
        return seq[l];
    int mid = (l + r) >> 1;
    int ans = max(solve(l, mid), solve(mid + 1, r));
    // first condition;
    // lft mx mi;
    int lptr = mid, rptr = mid + 1, lmx = seq[lptr], lmi = seq[lptr], suf = 0, pre = 0;
    while (lptr >= l)
    {
        pre ^= seq[lptr], lmx = max(lmx, seq[lptr]), lmi = min(lmi, seq[lptr]);
        while (rptr <= r && seq[rptr] <= lmx && seq[rptr] >= rptr)
            suf ^= seq[rptr], insert(suf), rptr++;
        ans = min(ans, query(pre ^ lmx ^ lmi));
        lptr--;
    }
    // second condition;
    // rig mx mi;
    lptr = mid, rptr = mid + 1, suf = pre = 0, reset();
    int rmx = seq[rptr], rmi = seq[rptr];
    while (rptr <= r)
    {
        suf ^= seq[rptr], rmx = max(seq[rptr], rmx), rmi = min(seq[rptr], rmi);
    }
}

void subtask()
{
    int ans = 0;
    for (int i = 1; i <= n; i++)
        insert(prefix[i]), ans = max(ans, query(prefix[i] ^ seq[i]));
    printf("%d", ans);
    exit(0);
}

int main()
{
    scanf("%d", &n);
    bool flag1 = true, flag2 = true, flag3 = true;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &prefix[i]), seq[i] = prefix[i], cnt = max(cnt, prefix[i]);
        flag3 &= (prefix[i] <= 1 && prefix[i] >= 0);
        if (i > 1)
            flag1 &= (prefix[i] > prefix[i - 1]), flag2 &= (prefix[i] < prefix[i - 1]);
    }
    if (flag3)
        printf("%d\n", cnt), exit(0);
    for (int i = 1; i <= n; i++)
        prefix[i] ^= prefix[i - 1];
    if (flag1 || flag2)
        subtask();
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i, mx_val = seq[i], mi_val = seq[i]; j <= n; j++)
        {
            mx_val = max(mx_val, seq[j]), mi_val = min(mi_val, seq[j]);
            ans = max(ans, prefix[j] ^ prefix[i - 1] ^ mx_val ^ mi_val);
        }
    printf("%d", ans);
    return 0;
}