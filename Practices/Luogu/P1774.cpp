// P1774.cpp
#include <iostream>
#include <algorithm>

using namespace std;

const long long maxn = 500020;
const long long INF = 0x7fffffff;
long long n;
long long arr[maxn];
long long C[maxn * 2];
long long p[maxn];

inline long long lowbit(long long n)
{
    return n & (-n);
}

void Add(long long x, long long d)
{
    while (x <= n)
        C[x] += d, x += lowbit(x);
}

long long Query(long long idx)
{
    long long ret = 0;
    while (idx > 0)
        ret += C[idx], idx -= lowbit(idx);
    return ret;
}

bool cmp(long long a, long long b)
{
    return arr[a] < arr[b];
}

int main()
{
    fill(C, C + 2 * n, 0);
    cin >> n;
    for (long long i = 1; i <= n; i++)
        cin >> arr[i], p[i] = i;
    stable_sort(p + 1, p + n + 1, cmp);
    // make dataset lighter.
    for (long long i = 1; i <= n; i++)
        arr[p[i]] = i;
    long long ans = 0;
    for (long long i = n; i >= 1; i--)
        ans += Query(arr[i] - 1), Add(arr[i], 1);
    cout << ans;
    return 0;
}