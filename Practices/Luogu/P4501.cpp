// P4501.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

ll n, m, K, ai[MAX_N], li[MAX_N], log2_[MAX_N], rk[MAX_N], tmp[MAX_N], dist[MAX_N];

inline char nc()
{
    static char buf[1 << 20], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

struct STable
{
    ll mat[20][MAX_N];

    void init()
    {
        for (int i = 1; i < 20; i++)
            for (int j = 1; j + (1 << i) - 1 <= K; j++)
                mat[i][j] = min(mat[i - 1][j], mat[i - 1][j + (1 << (i - 1))]);
    }

    ll query(int l, int r)
    {
        int d = log2_[r - l + 1];
        return min(mat[d][l], mat[d][r - (1 << d) + 1]);
    }
} st[2];

int lower(int val)
{
    int l = 1, r = K, res = K + 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (tmp[mid] < val)
            l = mid + 1;
        else
            r = mid - 1, res = mid;
    }
    return res;
}

int upper(int val)
{
    int l = 1, r = K, res = K + 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (tmp[mid] <= val)
            l = mid + 1;
        else
            r = mid - 1, res = mid;
    }
    return res;
}

int main()
{
    n = read(), m = read();
    for (int i = 2; i <= n; i++)
        dist[i] = dist[i - 1] + read(), log2_[i] = log2_[i >> 1] + 1;
    while (m--)
    {
        ll ans = 0;
        K = read();
        for (int i = 1; i <= K; i++)
            ai[i] = read(), li[i] = read(), tmp[i] = ai[i];
        sort(tmp + 1, tmp + 1 + K);
        for (int i = 1; i <= K; i++)
            rk[tmp[i]] = i;
        for (int i = 1; i <= K; i++)
        {
            st[0].mat[0][rk[ai[i]]] = li[i] - dist[ai[i]];
            st[1].mat[0][rk[ai[i]]] = li[i] + dist[ai[i]];
        }
        st[0].init(), st[1].init();
        for (int i = 1; i <= K; i++)
        {
            int l = 1, r = ai[i] - 1, lft = ai[i], rig = ai[i];
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                ll cdist = li[i] + dist[ai[i]] - dist[mid], diff = ai[i] - mid;
                ll ql = 0x3f3f3f3f3f3f3f3f, qr = ql;

                int qlft = lower(max(1LL, mid - diff));
                int qrig = upper(mid) - 1;
                if (qlft <= qrig)
                    ql = st[0].query(qlft, qrig);

                qlft = lower(mid);
                qrig = upper(ai[i] - 1) - 1;

                if (qlft <= qrig)
                    qr = st[1].query(qlft, qrig);
                bool flag = (ql + dist[mid] > cdist) && (qr - dist[mid] > cdist);
                if (flag)
                    r = mid - 1, lft = mid;
                else
                    l = mid + 1;
            }
            l = ai[i] + 1, r = n;
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                ll cdist = li[i] + dist[mid] - dist[ai[i]], diff = mid - ai[i];
                ll ql = 0x3f3f3f3f3f3f3f3f, qr = ql;

                int qlft = lower(mid);
                int qrig = upper(min(mid + diff - 1, 1LL * n)) - 1;
                if (qlft <= qrig)
                    qr = st[1].query(qlft, qrig);

                qlft = lower(ai[i] + 1);
                qrig = upper(mid) - 1;

                if (qlft <= qrig)
                    ql = st[0].query(qlft, qrig);
                bool flag = (ql + dist[mid] > cdist) && (qr - dist[mid] > cdist);
                if (mid + diff <= n)
                {
                    qrig = upper(mid + diff) - 1;
                    if (tmp[qrig] == mid + diff && st[1].mat[0][qrig] - dist[mid] < cdist)
                        flag = false;
                }
                if (flag)
                    l = mid + 1, rig = mid;
                else
                    r = mid - 1;
            }
            ans += rig - lft + 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}