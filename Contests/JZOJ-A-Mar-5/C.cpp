// C.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 101000;
ll n, l, w, pos[MAX_N], prefix[MAX_N], answer;
bool validiate(int l, int r)
{
    int mid = (l + r) >> 1;
    ll ans = pos[mid] * (mid - l + 1) - (prefix[mid] - prefix[l - 1]) + (prefix[r] - prefix[mid]) - pos[mid] * (r - mid);
    return ans <= w;
}
int main()
{
    scanf("%lld%lld%lld", &n, &l, &w);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &pos[i]), prefix[i] = prefix[i - 1] + pos[i];
    ll lcur = 1, rcur = 0;
    while (rcur < n && lcur <= n)
    {
        rcur++;
        while (lcur <= rcur && !validiate(lcur, rcur))
            lcur++;
        answer = max(rcur - lcur + 1, answer);
    }
    printf("%lld", answer);
    return 0;
}