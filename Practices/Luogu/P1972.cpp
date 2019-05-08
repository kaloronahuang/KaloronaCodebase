// P1972.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 501000;

int n, m, arr[MAX_N], lft[MAX_N], rig[MAX_N], len, tot, cnt[1000005];
int anses[MAX_N];

struct element
{
    int id, ql, qr, ans, aff;
    bool operator<(const element &ele) const { return aff == ele.aff ? (aff & 1) ? qr < ele.qr : qr > ele.qr : ql < ele.ql; }
} queries[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    scanf("%d", &m), len = sqrt(m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &queries[i].ql, &queries[i].qr), queries[i].id = i, queries[i].aff = queries[i].ql / len;
    sort(queries + 1, queries + 1 + m);
    int preL = 0, preR = 0, ans = 0;
    for (int i = 1; i <= m; i++)
    {
        int cL = queries[i].ql, cR = queries[i].qr;
        if (preL < cL)
            for (int ptr = preL; ptr < cL; ptr++)
                cnt[arr[ptr]]--, ans -= (cnt[arr[ptr]] == 0 ? 1 : 0);
        else if (preL > cL)
            for (int ptr = preL - 1; ptr >= cL; ptr--)
                cnt[arr[ptr]]++, ans += (cnt[arr[ptr]] == 1 ? 1 : 0);

        if (preR > cR)
            for (int ptr = preR; ptr > cR; ptr--)
                cnt[arr[ptr]]--, ans -= (cnt[arr[ptr]] == 0 ? 1 : 0);
        else if (preR < cR)
            for (int ptr = preR + 1; ptr <= cR; ptr++)
                cnt[arr[ptr]]++, ans += (cnt[arr[ptr]] == 1 ? 1 : 0);
        anses[queries[i].id] = ans;
        preL = cL, preR = cR;
    }
    for (int i = 1; i <= m; i++)
        printf("%d\n", anses[i]);
    return 0;
}