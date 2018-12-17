// POJ2182.cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define lowbit(num) (num & -num)
using namespace std;
const int maxn = 8800;
int tree[maxn], n, arr[maxn], height[maxn];
bool ansbox[maxn];
void add(int x, int c)
{
    while (x <= n)
        tree[x] += c, x += lowbit(x);
}
int sum(int x)
{
    int ret = 0;
    while (x > 0)
        ret += tree[x], x -= lowbit(x);
    return ret;
}
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        scanf("%d", &arr[i]), arr[i]++;
    // init;
    for (int i = 1; i <= n; i++)
        add(i, 1);
    for (int i = n; i >= 2; i--)
    {
        int tar = arr[i], p = 1, pos = 0;
        while (p)
            if (pos + p <= n && sum(pos + p) < tar)
                pos += p, p <<= 1;
            else
                p >>= 1;
        pos++;
        height[i] = pos;
        ansbox[pos] = true;
        add(pos, -1);
    }
    for (int i = 1; i <= n; i++)
        if (!ansbox[i])
        {
            height[1] = i;
            break;
        }
    for (int i = 1; i <= n; i++)
        printf("%d\n", height[i]);
    return 0;
}