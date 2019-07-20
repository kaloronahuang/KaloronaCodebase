// D.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll T, n, k;

int main()
{
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld%lld", &n, &k);
        bool win = true;
        if (k % 3 == 0)
        {
            int np = n % (k + 1);
            if (np % 3 == 0 && np != k)
                win = false;
        }
        else
        {
            if (n % 3 == 0)
                win = false;
        }
        puts(win ? "Alice" : "Bob");
    }
    return 0;
}