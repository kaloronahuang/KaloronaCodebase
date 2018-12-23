// P1034.cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
int n, k, arr[10], ans = 0x7fffffff;
bool vis[55];
struct vec
{
    int x, y;
} vecs[60];
bool compareX(const vec &v1, const vec &v2) { return v1.x < v2.x || (v1.x == v2.x && v1.y < v2.y); }
bool compareY(const vec &v1, const vec &v2) { return v1.y < v2.y || (v1.y == v2.y && v1.x < v2.x); }
void doStatistics()
{
    int tmpsiz = 0;
    for (int i = 1; i <= k; i++)
    {
        int mxx = 0, mxy = 0, mix = 0x3f3f3f3f, miy = 0x3f3f3f3f;
        for (int j = arr[i - 1] + 1; j <= arr[i]; j++)
        {
            mxx = max(mxx, vecs[j].x), mix = min(mix, vecs[j].x);
            mxy = max(mxy, vecs[j].y), miy = min(miy, vecs[j].y);
        }
        tmpsiz += (mxx - mix) * (mxy - miy);
    }
    ans = min(ans, tmpsiz);
}
void search(int remain)
{
    if (remain == k)
    {
        doStatistics();
        return;
    }
    for (int i = arr[remain - 1] + 1; i <= n; i++)
        if (!vis[i])
        {
            vis[i] = true;
            arr[remain] = i;
            search(remain + 1);
            vis[i] = false;
        }
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &vecs[i].x, &vecs[i].y);
    sort(vecs + 1, vecs + 1 + n, compareX);
    arr[k] = n;
    search(1);
    sort(vecs + 1, vecs + 1 + n, compareY);
    search(1);
    printf("%d", ans);
    return 0;
}