// C.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long prod, ans;
    scanf("%lld", &prod);
    ans = prod - 1;
    for (int i = 2; 1LL * i * i <= prod; i++)
        if (prod % i == 0)
            ans = min(ans, (prod / i) + i - 2);
    printf("%lld", ans);
    return 0;
}