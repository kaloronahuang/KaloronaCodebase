// POJ3613.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int MAX_N = 110;

int n, t, s, e, mat[MAX_N][MAX_N], tmp[MAX_N][MAX_N], ans[MAX_N][MAX_N], tot;
vector<int> vec;

struct edge
{
    int src, dst, len;
} edges[MAX_N];

void quick_pow(int tim)
{
    memcpy(ans, mat, sizeof(ans));
    tim--;
    while (tim)
    {
        if (tim & 1)
        {
            memset(tmp, 0x3f, sizeof(tmp));
            for (int i = 1; i <= tot; i++)
                for (int j = 1; j <= tot; j++)
                    for (int k = 1; k <= tot; k++)
                        tmp[i][j] = min(tmp[i][j], ans[i][k] + mat[k][j]);
            memcpy(ans, tmp, sizeof(tmp));
        }
        memset(tmp, 0x3f, sizeof(tmp));
        for (int i = 1; i <= tot; i++)
            for (int j = 1; j <= tot; j++)
                for (int k = 1; k <= tot; k++)
                    tmp[i][j] = min(tmp[i][j], mat[i][k] + mat[k][j]);
        memcpy(mat, tmp, sizeof(tmp));
        tim >>= 1;
    }
}

int main()
{
    memset(mat, 0x3f, sizeof(mat));
    scanf("%d%d%d%d", &n, &t, &s, &e);
    for (int i = 1; i <= t; i++)
        scanf("%d%d%d", &edges[i].len, &edges[i].src, &edges[i].dst), vec.push_back(edges[i].src), vec.push_back(edges[i].dst);
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end()), tot = vec.size();
    for (int i = 1; i <= t; i++)
    {
        edges[i].src = lower_bound(vec.begin(), vec.end(), edges[i].src) - vec.begin() + 1;
        edges[i].dst = lower_bound(vec.begin(), vec.end(), edges[i].dst) - vec.begin() + 1;

        mat[edges[i].src][edges[i].dst] = mat[edges[i].dst][edges[i].src] = min(mat[edges[i].src][edges[i].dst], edges[i].len);
    }
    s = lower_bound(vec.begin(), vec.end(), s) - vec.begin() + 1;
    e = lower_bound(vec.begin(), vec.end(), e) - vec.begin() + 1;
    quick_pow(n);
    printf("%d", ans[s][e]);
    return 0;
}