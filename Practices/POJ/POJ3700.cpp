// POJ3700.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 70;
int heights[maxn], n, dep;
vector<int> up, down;
bool dfs(int x)
{
    if (up.size() + down.size() > dep)
        return false;
    if (x == n + 1)
        return true;
    // process seperately;
    int siz = up.size(), num = 0, id;
    for (int i = 0; i < siz; i++)
        if (up[i] > num && heights[x] > up[i])
            num = up[i], id = i;
    if (num)
    {
        up[id] = heights[x];
        if (dfs(x + 1))
            return true;
        up[id] = num;
    }
    else
    {
        up.push_back(heights[x]);
        if (dfs(x + 1))
            return true;
        up.pop_back();
    }
    siz = down.size(), num = 2e9, id;
    for (int i = 0; i < siz; i++)
        if (down[i] < num && heights[x] < down[i])
            num = down[i], id = i;
    if (num != 2e9)
    {
        down[id] = heights[x];
        if (dfs(x + 1))
            return true;
        down[id] = num;
    }
    else
    {
        down.push_back(heights[x]);
        if (dfs(x + 1))
            return true;
        down.pop_back();
    }
    return false;
}
int main()
{
    while (scanf("%d", &n) && n != 0)
    {
        for (int i = 1; i <= n; i++)
            scanf("%d", &heights[i]);
        dep = 0;
        up.clear(), down.clear();
        while (!dfs(1))
            dep++;
        printf("%d\n", dep);
    }
    return 0;
}