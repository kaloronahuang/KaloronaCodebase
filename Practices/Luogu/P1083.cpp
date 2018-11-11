// P1083.cpp
#include <iostream>

using namespace std;

const int maxn = 1000200;
const int INF = 0x7fffffff;
int arr[maxn], diff[maxn], d[maxn], l[maxn], r[maxn], need[maxn];
int n, m;

bool judge(int x)
{
    fill(diff, diff + maxn, 0);
    for (int i = 1; i <= x; i++)
        diff[l[i]] += d[i], diff[r[i] + 1] -= d[i];
    for (int i = 1; i <= n; i++)
    {
        need[i] = need[i - 1] + diff[i];
        if (need[i] > arr[i])
            return false;
    }
    return true;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    for (int i = 1; i <= m; i++)
        cin >> d[i] >> l[i] >> r[i];
    int left = 1;
    int right = n;
    if (judge(n))
    {
        cout << 0;
        return 0;
    }
    while (left < right)
    {
        int mid = (left + right) >> 1;
        if (judge(mid))
            left = mid + 1;
        else
            right = mid;
    }
    cout << -1 << endl
         << left;
    return 0;
}