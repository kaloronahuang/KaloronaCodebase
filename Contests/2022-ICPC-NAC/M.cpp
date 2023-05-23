// M.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
set<ll> occurance;

void print(ll x)
{
    for (int i = 0; i < 10; i++)
        putchar(x % 26 + 'a'), x /= 26;
    puts("");
}

bool check_near(ll u)
{
    for (ll i = 0, bas = 1; i < 10; i++, bas *= 26)
    {
        ll pos_c = (u / bas) % 26;
        for (ll c = 0; c < 26; c++)
            if (c != pos_c)
            {
                ll new_stat = u + (c - pos_c) * bas;
                if (occurance.count(new_stat) == 1)
                    return false;
            }
    }
    return true;
}

int main()
{
    scanf("%d", &n);
    ll ustat = 0;
    while (n--)
    {
        print(ustat);
        // find next;
        bool output = false;
        ll pre_stat = ustat;
        for (ll i = 0, bas = 1; i < 10; i++, bas *= 26)
        {
            ll pos_c = (pre_stat / bas) % 26;
            for (ll c = 0; c < 26; c++)
                if (c != pos_c)
                {
                    ll new_stat = ustat + (c - pos_c) * bas;
                    if (occurance.count(new_stat) == 0 && check_near(new_stat))
                    {
                        ustat = new_stat;
                        output = true;
                        break;
                    }
                }
            if (output)
                break;
        }
        occurance.insert(pre_stat);
    }
    return 0;
}