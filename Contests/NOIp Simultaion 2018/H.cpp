// H.cpp
#include <iostream>
#include <map>
using namespace std;
const int maxn = 25157890;
#define ll long long
ll arr[maxn];
ll n;
ll ans = 0;
map<string, int> mp;

void mergeSort(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (l <= mid)
        mergeSort(l, mid);
    if (r > mid)
        mergeSort(mid + 1, r);

    ll tmp[r - l + 1];
    int a = l;
    int b = mid + 1;
    int cur = 0;
    while (a <= mid && b <= r)
        if (arr[a] > arr[b])
            ans += (mid - a + 1), tmp[cur++] = arr[b++];
        else
            tmp[cur++] = arr[a++];
    while (a <= mid)
        tmp[cur++] = arr[a++];
    while (b <= r)
        tmp[cur++] = arr[b++];
    cur = l;
    for (int i = 0; i < r - l + 1; i++)
        arr[cur++] = tmp[i];
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string str;
        cin >> str;
        mp.insert(pair<string, int>(str, i));
    }
    for (int i = 1; i <= n; i++)
    {
        string str;
        cin >> str;
        arr[i] = mp[str];
    }
    mergeSort(1, n);
    cout << ans;
    return 0;
}