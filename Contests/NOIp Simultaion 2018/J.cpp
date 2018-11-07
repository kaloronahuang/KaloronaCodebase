// J.cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define ll long long
const ll maxn = 100200;
ll n, k;
ll arr[maxn];
ll que[maxn];
ll q[maxn];

void swap()
{
    for (int i = 1; i <= n; i++)
        q[i] = que[i];
    for (int i = 1; i <= n; i++)
        que[arr[i]] = q[i];
}

int main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]), que[i] = i;
    k %= (n + 1);
    while (k--)
        swap();
    for (int i = 1; i <= n; i++)
        printf("%lld ", que[i]);
    return 0;
}