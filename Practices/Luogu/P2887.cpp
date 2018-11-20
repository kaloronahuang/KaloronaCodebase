// POJ3614.cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 2600;
struct cow
{
    int minSPF, maxSPF;
    bool operator<(const cow &cw) const
    {
        return minSPF > cw.minSPF;
    }
} cows[maxn];
struct lotion
{
    int SPF, cover;
    bool operator<(const lotion &cw) const
    {
        return SPF > cw.SPF;
    }
} lotions[maxn];
int c, l;

int main()
{
    scanf("%d%d", &c, &l);
    for (int i = 1; i <= c; i++)
        scanf("%d%d", &cows[i].minSPF, &cows[i].maxSPF);
    for (int i = 1; i <= l; i++)
        scanf("%d%d", &lotions[i].SPF, &lotions[i].cover);
    sort(cows + 1, cows + 1 + c);
    sort(lotions + 1, lotions + 1 + l);
    int ans = 0;
    for (int i = 1; i <= c; i++)
        for (int j = 1; j <= l; j++)
            if (cows[i].maxSPF >= lotions[j].SPF && cows[i].minSPF <= lotions[j].SPF && lotions[j].cover > 0)
            {
                ans++, lotions[j].cover--;
                break;
            }
    printf("%d", ans);
    return 0;
}