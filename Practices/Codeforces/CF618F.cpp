// CF618F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000100;

typedef long long ll;

int n;
ll prefix[2][MAX_N];
pair<int, int> tag[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < 2; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &prefix[i][j]), prefix[i][j] += prefix[i][j - 1];
    for (int i = 0; i <= n; i++)
        tag[i] = make_pair(-1, -1);
    bool swapped = false;
    if (prefix[0][n] < prefix[1][n])
        swap(prefix[0], prefix[1]), swapped = true;
    ll ptrA = 0, ptrB = 0, diff = 0;
    for (; ptrA <= n; ptrA++)
    {
        while (prefix[0][ptrA] >= prefix[1][ptrB + 1] && ptrB + 1 <= n)
            ptrB++;
        diff = prefix[0][ptrA] - prefix[1][ptrB];
        if (tag[diff].first == -1)
            tag[diff] = make_pair(ptrA, ptrB);
        else
            break;
    }
    if (swapped)
        swap(prefix[0], prefix[1]), swap(tag[diff].first, tag[diff].second), swap(ptrA, ptrB);
    printf("%lld\n", ptrA - tag[diff].first);
    for (int i = tag[diff].first + 1; i <= ptrA; i++)
        printf("%d ", i);
    puts("");
    printf("%lld\n", ptrB - tag[diff].second);
    for (int i = tag[diff].second + 1; i <= ptrB; i++)
        printf("%d ", i);
    puts("");
    return 0;
}