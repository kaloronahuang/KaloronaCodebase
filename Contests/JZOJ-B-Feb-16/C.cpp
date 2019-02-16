// C.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 100010;
int arr[MAX_N], n, k, p, tot, desire;
ll sum[MAX_N];
bool check(ll num)
{
    int tim = n + 2;
    srand(time(NULL));
    int i = rand() % n + 1, j = rand() % n + 1;
    int i2 = rand() % n + 1, j2 = rand() % n + 1;
    while (tim--)
    {
        if (i > j)
            swap(i, j);
        if (i2 > j2)
            swap(i2, j2);
        int key1 = (sum[j] - sum[i]) % p;
        if (key1 >= k && key1 <= num)
            return true;
        int key2 = (sum[j2] - sum[i2]) % p;
        if (key2 >= k && key2 <= num)
            return true;
        i = rand() % n + 1, j = rand() % n + 1;
        i2 = rand() % n + 1, j2 = rand() % n + 1;
    }
    return false;
}
int main()
{
    scanf("%d%d%d", &n, &k, &p);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), sum[i] = sum[i - 1] + arr[i];
    ll l = k, r = p - 1;
    while (l < r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    printf("%lld", l);
    return 0;
}