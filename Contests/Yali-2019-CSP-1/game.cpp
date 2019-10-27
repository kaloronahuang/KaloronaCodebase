// game.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 101000;

multiset<int> ms;
int n, ai[MAX_N], bi[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    sort(ai + 1, ai + 1 + n);
    for (int i = 1, tmp; i <= n; i++)
        scanf("%d", &tmp), ms.insert(tmp);
    for (int i = n; i >= 1; i--)
    {
        multiset<int>::iterator it = ms.upper_bound(ai[i]);
        if (it == ms.end())
            bi[i] = *ms.begin(), ms.erase(ms.begin());
        else
            bi[i] = *it, ms.erase(it);
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", bi[i]);
    return 0;
}