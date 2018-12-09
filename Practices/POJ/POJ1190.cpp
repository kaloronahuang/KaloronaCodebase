// POJ1190.cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 21;
int N, M, h[maxn], r[maxn], ans = 1e9;
int minv[maxn], mins[maxn];
int sa, vol;
void dfs(int dep)
{
    if (dep == 0)
    {
        if (vol == N)
            ans = min(ans, sa);
        return;
    }
    for (r[dep] = min((int)(sqrt(N - vol)), r[dep + 1] - 1); r[dep] >= dep; r[dep]--)
        for (h[dep] = min((int)((N - vol) / r[dep] / r[dep]), h[dep + 1] - 1); h[dep] >= dep; h[dep]--)
        {
            if (vol + minv[dep - 1] > N)
                continue;
            if (sa + mins[dep - 1] > ans)
                continue;
            if (sa + (double)2 * (N - vol) / r[dep] > ans)
                continue;
            if (dep == M)
                sa += r[dep] * r[dep];
            vol += r[dep] * r[dep] * h[dep];
            sa += 2 * r[dep] * h[dep];
            dfs(dep - 1);
            if (dep == M)
                sa -= r[dep] * r[dep];
            vol -= r[dep] * r[dep] * h[dep];
            sa -= 2 * r[dep] * h[dep];
        }
}

int main()
{
    scanf("%d%d", &N, &M);
    for (int i = 1; i < maxn; i++)
        minv[i] = minv[i - 1] + i * i * i, mins[i] = mins[i - 1] + i * i;
    h[M + 1] = r[M + 1] = 1e9;
    dfs(M);
    printf("%d", ans);
    return 0;
}