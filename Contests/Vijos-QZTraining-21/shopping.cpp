// shopping.cpp
#include <bits/stdc++.h>

using namespace std;

int n, opt, tmp;
long long ans;
multiset<int> ms;

int main()
{
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d%d", &opt, &tmp);
        if (opt == 1)
            if (!ms.empty())
            {
                multiset<int>::iterator it = ms.lower_bound(tmp);
                if (it != ms.begin())
                    it--, ans += (tmp - *it), ms.erase(it);
                else
                    ans += tmp;
            }
            else
                ans += tmp;
        else
            ms.insert(tmp);
    }
    printf("%lld", ans);
    return 0;
}