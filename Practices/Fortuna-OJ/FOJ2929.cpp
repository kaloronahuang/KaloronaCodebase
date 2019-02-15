// FOJ2929.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1001000;
map<int, int> mp;
pair<int, int> pts[MAX_N];
int n, dist;
void add(int x)
{
    if (mp[x] == 0)
        dist++;
    mp[x]++;
}
void remove(int x)
{
    mp[x]--;
    if (mp[x] == 0)
        dist--;
}
bool judge()
{
    sort(pts + 1, pts + 1 + n);
    dist = 0, mp.clear();
    for (int i = 1; i <= n; i++)
        add(pts[i].second);
    if (dist <= 3)
        return true;
    int i = 1, i1 = 1;
    while (i <= n)
    {
        while (pts[i].first == pts[i1].first && i1 <= n)
            i1++;
        for (int i2 = i; i2 < i1; i2++)
            remove(pts[i2].second);
        if (dist <= 2)
            return true;
        for (int i2 = i; i2 < i1; i2++)
            add(pts[i2].second);
        i = i1;
    }
    return false;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].first, &pts[i].second);
    if (judge())
        puts("1");
    else
    {
        for (int i = 1; i <= n; i++)
            swap(pts[i].first, pts[i].second);
        if (judge())
            puts("1");
        else
            puts("0");
    }
    return 0;
}