// P2698.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <deque>
#define pr pair<int, int>
using namespace std;
const int MX_N = 100200;
int keyNum, m;
pr drops[MX_N];
bool check(int width)
{
    int ans = 0;
    deque<int> q;
    for (int key = 1; key <= keyNum; key++)
    {
        pr curtdrop = drops[key];
        while (!q.empty() && drops[q.front()].first < curtdrop.first - width)
            q.pop_front();
        if (!q.empty())
            ans = max(ans, curtdrop.second - drops[q.front()].second);
        while (!q.empty() && drops[q.back()].second > curtdrop.second)
            q.pop_back();
        q.push_back(key);
    }
    return (ans >= m);
}

int main()
{
    scanf("%d%d", &keyNum, &m);
    int minval = 2e9, mxval = 0;
    for (int i = 1; i <= keyNum; i++)
    {
        scanf("%d%d", &drops[i].first, &drops[i].second);
        minval = min(minval, drops[i].second);
        mxval = max(mxval, drops[i].second);
    }
    if (mxval - minval < m)
    {
        printf("-1");
        return 0;
    }
    sort(drops + 1, drops + 1 + keyNum);
    int l = 1, r = drops[keyNum].first;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    printf("%d", l);
    return 0;
}