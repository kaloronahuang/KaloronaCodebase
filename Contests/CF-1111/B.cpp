// B.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 1e5 + 20000;
ll n, k, m, arr[MAX_N], sum[MAX_N];
int main()
{
    scanf("%lld%lld%lld", &n, &k, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]);
    sort(arr + 1, arr + 1 + n);
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + arr[i];
    ll ans = sum[n], personNum = n;
    for (int i = 0; i < n && i <= m; i++)
    {
        // i is for the deletion of people;
        ll pNum = n - i, addopt = m - i;
        addopt = min(addopt, k * pNum);
        ll son = sum[n] - sum[i] + addopt;
        if (son * personNum > ans * pNum)
            ans = son, personNum = pNum;
    }
    printf("%lf", double(ans) / double(personNum));
    return 0;
}