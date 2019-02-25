// B.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 2e6 + 20000;
const ll INF = (0x3f3f3f3f3f3f3f3f);
ll f[MAX_N], arr[MAX_N], n, k, c, q[MAX_N << 2];
int head = 1, tail = 0;
ll pow(ll num) { return num * num; }
double check(ll a, ll b)
{
    return ((f[b - 1] + pow(arr[b])) - (f[a - 1] + pow(arr[a]))) / (2.0 * (arr[b] - arr[a]));
}
void insert(int x)
{
    while (head <= tail && arr[q[tail]] == arr[x])
        if (f[x - 1] < f[q[tail] - 1])
            tail--;
        else
            return;
    while (head < tail && check(q[tail - 1], q[tail]) > check(q[tail], x))
        tail--;
    q[++tail] = x;
}
int main()
{
    freopen("work1.in", "r", stdin);
    scanf("%lld%lld%lld", &n, &k, &c);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]);
    f[0] = 0;
    sort(arr + 1, arr + 1 + n);
    for (int i = 1; i < k; i++)
        f[i] = INF;
    for (int i = k; i <= n; i++)
    {
        int x = i - k + 1;
        insert(x);
        while (head < tail && check(q[head], q[head + 1]) < arr[i])
            head++;
        f[i] = f[q[head] - 1] + c + pow(arr[q[head]] - arr[i]);
    }
    printf("%lld", f[n]);
    return 0;
}
