// CF1276C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

typedef pair<int, int> pii;

int n, ai[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    map<int, int> counter;
    for (int i = 1; i <= n; i++)
        counter[ai[i]]++;
    vector<pii> vec;
    for (auto x : counter)
        vec.push_back(make_pair(x.second, x.first));
    sort(vec.begin(), vec.end());
    int siz = vec.size(), p = 1, q = 1, ansArea = 1, curt = 0;
    for (int i = 1, ptr = 0; 1LL * i * i <= n; i++)
    {
        curt += siz - ptr;
        while (ptr < siz && (vec[ptr].first <= i))
            ptr++;
        int curt_siz = curt - curt % i;
        if (curt_siz > ansArea && curt_siz / i >= i)
            ansArea = curt_siz, p = i, q = curt_siz / i;
    }
    printf("%lld\n%d %d\n", 1LL * p * q, p, q);
    int ansBox[p][q], last_ptr = siz - 1, usage = 0;
    for (int i = 0; i < q; i++)
        for (int j = 0; j < p; j++)
        {
            ansBox[j][(j + i) % q] = vec[last_ptr].second, usage++;
            if (usage == min(p, vec[last_ptr].first))
                last_ptr--, usage = 0;
        }
    for (int i = 0; i < p; i++, puts(""))
        for (int j = 0; j < q; j++)
            printf("%d ", ansBox[i][j]);
    return 0;
}