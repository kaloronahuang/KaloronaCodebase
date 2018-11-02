#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int max(int x, int y) { return x > y ? x : y; }
int dp[101][1001]; //dp[i][j]表示在扔进去第i个辣鸡，在j的高度时的最大生命
struct trash
{
    int t, f, h;
    friend bool operator<(trash a, trash b)
    {
        return a.t < b.t;
    }
} r[101];
int main()
{
    memset(dp, -1, sizeof(dp));
    int d, g;
    scanf("%d%d", &d, &g);
    for (int i = 1; i <= g; i++)
        scanf("%d%d%d", &r[i].t, &r[i].f, &r[i].h);
    sort(r + 1, r + g + 1);
    dp[0][0] = 10;
    r[0].f = 0;
    r[0].h = 0;
    r[0].t = 0;
    for (int i = 0; i < g; i++)
        for (int j = 0; j <= d; j++)
        {
            if (dp[i][j] < 0) //没有奶牛的状态
                continue;
            if (j + r[i + 1].h >= d && dp[i][j] >= r[i + 1].t - r[i].t) //转移这个状态时，既满足下一个垃圾可以直接跳出去，又满足奶牛的能量能坚持到下一个垃圾。
            {
                printf("%d\n", r[i + 1].t);
                return 0;
            }
            if (dp[i][j] - r[i + 1].t + r[i].t >= 0)
                dp[i + 1][j + r[i + 1].h] = dp[i][j] - r[i + 1].t + r[i].t;
            if (dp[i][j] - r[i + 1].t + r[i].t >= 0)
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] - r[i + 1].t + r[i].t + r[i + 1].f); //这里max因为dp[i+1][j]可能本来有值
        }
    //如果进行到当前状态，说明没能跳出去
    //全吃掉 重新模拟一遍
    //当奶牛不能坚持时，要将现在的能量用完
    int m = 10, sum = 0; //m是现有能量，sum是已经用过的能量
    for (int i = 1; i <= g; i++)
    {
        if (r[i].t - r[i - 1].t > m)
        {
            printf("%d\n", sum + m);
            return 0;
        }
        sum += r[i].t - r[i - 1].t;
        m -= r[i].t - r[i - 1].t;
        m += r[i].f;
    }
    printf("%d\n", sum + m);
    return 0;
}