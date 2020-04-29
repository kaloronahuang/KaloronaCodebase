// P3537.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_Q = 1e6 + 200;

int n, q, dp[MAX_N];
bool ans[MAX_Q];

struct vec3
{
    int a, b, c;
    bool operator<(const vec3 &rhs) const { return a < rhs.a; }
} vecs[MAX_N];

struct queryInfo
{
    int m, k, s, id;
    bool operator<(const queryInfo &rhs) const { return m < rhs.m; }
} queries[MAX_Q];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &vecs[i].c, &vecs[i].a, &vecs[i].b);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
        scanf("%d%d%d", &queries[i].m, &queries[i].k, &queries[i].s), queries[i].id = i;
    sort(vecs + 1, vecs + 1 + n), sort(queries + 1, queries + 1 + q);
    int ptr = 1;
    dp[0] = 1e9;
    for (int i = 1; i <= q; i++)
    {
        while (ptr <= n && vecs[ptr].a <= queries[i].m)
        {
            for (int j = MAX_N - 1; j >= vecs[ptr].c; j--)
                dp[j] = max(dp[j], min(dp[j - vecs[ptr].c], vecs[ptr].b));
            ptr++;
        }
        ans[queries[i].id] = (dp[queries[i].k] > queries[i].m + queries[i].s);
    }
    for (int i = 1; i <= q; i++)
        puts(ans[i] ? "TAK" : "NIE");
    return 0;
}