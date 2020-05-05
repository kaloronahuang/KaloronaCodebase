// CF1348D.cpp
#include <bits/stdc++.h>

using namespace std;

int T, n;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        int base = 1;
        vector<int> vec;
        while (base <= n)
            vec.push_back(base), n -= base, base *= 2;
        if (n)
            vec.push_back(n);
        sort(vec.begin(), vec.end());
        printf("%lld\n", 1LL * vec.size() - 1);
        for (int i = 1, siz = vec.size(); i < siz; i++)
            printf("%d ", vec[i] - vec[i - 1]);
        puts("");
    }
    return 0;
}