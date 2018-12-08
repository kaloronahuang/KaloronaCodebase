// POJ1190.cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 21;
int N, M, h[maxn], r[maxn], ans = 1e9;
bool dfs(int dep, int siz, int v)
{
    if (dep == 0 && siz + r[M] * r[M] < ans && v == N)
    {
        ans = siz + r[M] * r[M];
        return true;
    }
    else if (dep == 0)
        return false;
    if (v > N || siz + r[M] > ans)
        return false;
    for (int R = min((int)sqrt(N - v), r[dep + 1] - 1); R >= dep; R--)
        for (int H = min(h[dep + 1] - 1, (N - v) / (R * R)); H >= dep; H--)
        {
            r[dep] = R, h[dep] = H;
            if (dfs(dep - 1, siz + 2 * R * H, v + R * R * H))
                return true; 
        }
    return false;
}
int main()
{
    scanf("%d%d", &N, &M);
    if (dfs(M, 0, 0))
        printf("%d", ans);
    else
        printf("0");
    return 0;
}