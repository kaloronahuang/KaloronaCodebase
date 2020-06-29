// E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1050;

int n, sum, ai[MAX_N], res[MAX_N], candid[MAX_N], pos[MAX_N];
int upper, lower, sa[MAX_N], sb[MAX_N], ans[MAX_N], ansptr;

bool compare(const int &x, const int &y)
{
    if ((ai[x] == lower) == (ai[y] == lower))
        return x < y;
    else
        return (ai[x] == lower) < (ai[y] == lower);
}

void solve(int len)
{
    bool found = false;
    for (int i = 1; i <= len; i++)
        ai[pos[i]]--;
    int min_val = *min_element(ai + 1, ai + 1 + n), max_val = *max_element(ai + 1, ai + 1 + n);
    if ((min_val << 1) >= max_val)
    {
        for (int i = 1; i <= len; i++)
            res[i] = pos[i];
        sort(res + 1, res + 1 + len), found = true;
    }
    else if (((min_val << 1) | 1) == max_val)
    {
        upper = max_val, lower = min_val;
        int ptra = 1, ptrb = 1, la = 0, lb = 0, ptr = 0;
        for (int i = 1; i <= len; i++)
            if (ai[pos[i]] == min_val || ai[pos[i]] == max_val)
                sa[++la] = pos[i];
            else
                sb[++lb] = pos[i];
        sort(sa + 1, sa + 1 + la, compare), sort(sb + 1, sb + 1 + lb);
        // merge;
        while (ptra <= la && ptrb <= lb)
            if (sa[ptra] < sb[ptrb])
                res[++ptr] = sa[ptra++];
            else
                res[++ptr] = sb[ptrb++];
        while (ptra <= la)
            res[++ptr] = sa[ptra++];
        while (ptrb <= lb)
            res[++ptr] = sb[ptrb++];
        found = true;
        for (int i = len + 1; i <= n; i++)
            if (ai[pos[i]] == min_val)
                found = false;
        found |= (ai[sa[1]] == max_val);
    }
    for (int i = 1; i <= len; i++)
        ai[pos[i]]++;
    if (!found)
        res[1] = 0;
}

bool lexicographicalCompare(int *s1, int *s2)
{
    int ptr = 1;
    while (s1[ptr] == s2[ptr])
        ptr++;
    return s1[ptr] < s2[ptr];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), sum += ai[i], pos[i] = i;
    if (((*min_element(ai + 1, ai + 1 + n)) << 1) < *max_element(ai + 1, ai + 1 + n))
        puts("-1"), exit(0);
    solve(n);
    for (int i = 1; i <= n; i++)
        ans[++ansptr] = res[i], ai[res[i]]--, pos[i] = res[i];
    while (ansptr < sum)
    {
        memset(candid, 0, sizeof(candid)), candid[1] = n + 1;
        int len = 0;
        for (int i = 1; i <= n; i++)
        {
            solve(i);
            if (res[1] != 0 && lexicographicalCompare(res, candid))
            {
                len = i;
                for (int j = 1; j <= i; j++)
                    candid[j] = res[j];
            }
        }
        for (int i = 1; i + len <= n; i++)
            pos[i] = pos[i + len];
        for (int i = 1; i <= len; i++)
            ans[++ansptr] = pos[n - len + i] = candid[i], ai[candid[i]]--;
    }
    for (int i = 1; i <= ansptr; i++)
        printf("%d ", ans[i]);
    puts("");
    return 0;
}