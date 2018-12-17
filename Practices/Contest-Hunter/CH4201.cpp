// CH4201.cpp
#include <iostream>
#include <cstdio>
#define ll long long
#define lowbit(num) (num & -num)
using namespace std;
const int maxn = 200100;
ll n, arr[maxn], ans, tree[maxn], leftv[maxn], rightv[maxn], leftuv[maxn], rightuv[maxn];
ll ansv, ansuv;
void add(int x, ll c)
{
    while (x <= n)
        tree[x] += c, x += lowbit(x);
}
ll sum(int x)
{
    ll res = 0;
    while (x > 0)
        res += tree[x], x -= lowbit(x);
    return res;
}
int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &arr[i]);
        leftv[i] = sum(arr[i]);
        rightv[i] = arr[i] - leftv[i] - 1;
        leftuv[i] = sum(n) - leftv[i];
        rightuv[i] = n - arr[i] - leftuv[i];
        ansv += leftv[i] * rightv[i];
        ansuv += leftuv[i] * rightuv[i];
        add(arr[i], 1);
    }
    printf("%lld %lld", ansuv, ansv);
    return 0;
}