// Beginner 114 C.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;
ll ans = 0, key;
void solve(ll sev, ll fif, ll th, ll pre)
{
    if (pre > key)
        return;
    else if (sev && fif && th)
        ans++;
    solve(sev + 1, fif, th, pre * 10 + 7);
    solve(sev, fif + 1, th, pre * 10 + 5);
    solve(sev, fif, th + 1, pre * 10 + 3);
}
int main()
{
    scanf("%lld", &key);
    solve(0, 0, 0, 0);
    cout << ans;
    return 0;
}