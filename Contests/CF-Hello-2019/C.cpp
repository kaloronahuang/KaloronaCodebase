// C.cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <vector>
#include <cstdlib>
#define ll long long
using namespace std;
const ll MX_N = 1e5 + 100;
ll n, arr[MX_N], lft[5 * MX_N], rig[5 * MX_N];
vector<string> strs;
string tmp;
ll numOfEmpty = 0;
int main()
{
    scanf("%I64d", &n);
    for (ll i = 1; i <= n; i++)
        cin >> tmp, strs.push_back(tmp);
    ll csiz = n;
    for (ll i = 0; i < csiz; i++)
    {
        string buff = strs[i];
        ll siz = buff.length();
        stack<ll> sl, sr;
        for (ll i = 0; i < siz; i++)
            if (buff[i] == '(')
                sr.push(1);
            else if (!sr.empty())
                sr.pop();
            else
                sl.push(1);
        ll l = sl.size(), r = sr.size();
        if (l == r && r == 0)
            numOfEmpty++;
        else if (l == 0)
            rig[r]++;
        else if (r == 0)
            lft[l]++;
    }
    ll res = 0;
    for (ll i = 0; i < 5 * MX_N; i++)
        res += min(lft[i], rig[i]);
    res += (numOfEmpty) >> 1;
    printf("%I64d", res);
    return 0;
}