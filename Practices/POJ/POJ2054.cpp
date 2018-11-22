// POJ2054.cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 1010;
int n, root, x, y;
struct node
{
    int tim, cost, fat;
    double w;
} nums[maxn];
int find_max()
{
    double val = 0;
    int id = 1;
    for (int i = 1; i <= n; i++)
        if (i != root && nums[i].w > val)
            id = i, val = nums[i].w;
    return id;
}
int main()
{
    while (scanf("%d%d", &n, &root) && n != 0)
    {
        long long ans = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &nums[i].cost), nums[i].w = nums[i].cost, nums[i].tim = 1, ans += nums[i].cost;
        for (int i = 1; i < n; i++)
            scanf("%d%d", &x, &y), nums[y].fat = x;
        for (int i = 1; i < n; i++)
        {
            int idx = find_max();
            nums[idx].w = 0;
            ans += nums[idx].cost * nums[nums[idx].fat].tim;
            for (int j = 1; j <= n; j++)
                if (nums[j].fat == idx)
                    nums[j].fat = nums[idx].fat;
            nums[nums[idx].fat].cost += nums[idx].cost;
            nums[nums[idx].fat].tim += nums[idx].tim;
            nums[nums[idx].fat].w = double(nums[nums[idx].fat].cost) / nums[nums[idx].fat].tim;
        }
        printf("%lld\n", ans);
    }
    return 0;
}