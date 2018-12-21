// BZ1053.cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;
const ll seq[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
ll limit, val, id = 2e9;
void dfs(ll pos, ll prev_num, ll prev_val, ll lit)
{
    if (prev_num > limit)
        return;
    if (pos == 10)
    {
        if (prev_val > val)
            val = prev_val, id = prev_num;
        else if (prev_val == val)
            id = min(id, prev_num);
        return;
    }
    ll num0 = prev_num;
    for (ll tim = 0; tim <= lit; tim++)
    {
        if (num0 > limit)
            return;
        dfs(pos + 1, num0, prev_val * (1 + tim), tim);
        num0 *= seq[pos];
    }
}
int main()
{
    scanf("%d", &limit);
    dfs(0, 1, 1, 0x7fffffff);
    printf("%d", id);
    return 0;
}