// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int n;

int main()
{
    scanf("%d", &n);
    int b = n & 1;
    n -= b;
    vector<pair<int, int>> ansBox;
    for (int i = 1; i <= (n << 1); i++)
    {
        for (int j = i + 1; j <= n; j++)
            if (j != i && j != (n - i + 1))
                ansBox.push_back(make_pair(i, j));
    }
    if (b)
    {
        n += b;
        for (int i = 1; i < n; i++)
            ansBox.push_back(make_pair(i, n));
    }
    printf("%lld\n", 1LL * ansBox.size());
    for (auto x : ansBox)
        printf("%d %d\n", x.first, x.second);
    return 0;
}