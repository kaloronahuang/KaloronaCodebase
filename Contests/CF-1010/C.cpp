// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, k, ai[MAX_N];
bool tag[MAX_N];

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    int d = ai[1];
    for (int i = 2; i <= n; i++)
        d = gcd(d, ai[i]);
    tag[0] = true, tag[d % k] = true;
    for (int i = (d + d) % k; i != d % k; i = (i + d) % k)
        tag[i] = true;
    vector<int> vec;
    for (int i = 0; i < k; i++)
        if (tag[i])
            vec.push_back(i);
    printf("%lld\n", 1LL * vec.size());
    for (auto x : vec)
        printf("%d ", x);
    return 0;
}