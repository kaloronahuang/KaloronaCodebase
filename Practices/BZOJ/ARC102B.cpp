// ARC102B.cpp
#include <bits/stdc++.h>

using namespace std;

vector<pair<pair<int, int>, int>> vec;

int main()
{
    int L;
    scanf("%d", &L);
    int cnt = 0;
    while (L >= (1 << (cnt + 1)))
        cnt++;
    int n = cnt + 1;
    for (int i = 1; i < n; i++)
    {
        vec.push_back(make_pair(make_pair(i, i + 1), 0));
        vec.push_back(make_pair(make_pair(i, i + 1), 1 << (i - 1)));
    }
    int acc = (1 << cnt);
    for (int i = 0; i < cnt; i++)
        if (L & (1 << i))
            vec.push_back(make_pair(make_pair(i + 1, n), acc)), acc += (1 << i);
    printf("%d %lld\n", n, 1LL * vec.size());
    for (auto x : vec)
        printf("%d %d %d\n", x.first.first, x.first.second, x.second);
    return 0;
}