// color_bf.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int T, p1, p2, k;
vector<int> mp;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &p1, &p2, &k);
        mp.clear();
        if (p1 > p2)
            swap(p1, p2);
        ll goal = 1LL * p1 / __gcd(p1, p2) * p2;
        for (ll i = 0; i <= goal; i += p1)
            mp.push_back(i);
        for (ll i = 0; i <= goal; i += p2)
            mp.push_back(i);
        sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
        int bottle_neck = 0, cnt = 0;
        for (int i = 0, siz = mp.size(); i < siz; i++)
            if (mp[i] % p2 == 0)
                bottle_neck = max(bottle_neck, cnt), cnt = 0;
            else if (mp[i] % p1 == 0)
                cnt++;
        bottle_neck = max(bottle_neck, cnt);
        puts(k <= bottle_neck ? "No" : "Yes");
    }
    return 0;
}