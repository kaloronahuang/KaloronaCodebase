// P1209.cpp
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 100000;
int M, S, C;
int intervals[maxn];
int nums[maxn];
int interval_num = 0;
int ans = 0;

void init()
{
    cin >> M >> S >> C;
    ans = C;
    for (int i = 0; i < C; i++)
        cin >> nums[i];
    sort(nums, nums + C);
    int pos = 0;
    while (pos < C - 1)
    {
        if (nums[pos + 1] - nums[pos] != 1)
            intervals[interval_num] = nums[pos + 1] - nums[pos] - 1, interval_num++;
        pos++;
    }
    sort(intervals, intervals + interval_num);
    return;
}

void solve()
{
    int ans = C;
    int block_num = interval_num + 1;
    int pos = 0;
    while (block_num > M)
    {
        ans += intervals[pos++];
        block_num--;
    }
    cout << ans;
}

int main()
{
    init();
    solve();
    return 0;
}