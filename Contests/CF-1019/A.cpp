// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030;

typedef long long ll;
typedef pair<int, int> pii;

int n, m, pi[MAX_N], ci[MAX_N], cnt[MAX_N], pcnt;
ll gans = 1e18;
pii people[MAX_N];
bool tag[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &pi[i], &ci[i]);
        if (pi[i] != 1)
            people[++pcnt] = make_pair(ci[i], pi[i]);
        else
            cnt[1]++;
    }
    sort(people + 1, people + 1 + pcnt);
    for (int stock = 1; stock <= n; stock++)
    {
        int rem = cnt[1];
        ll pans = 0;
        memset(tag, false, sizeof(tag));
        for (int i = 2; i <= m; i++)
            cnt[i] = 0;
        for (int i = 1; i <= pcnt; i++)
            cnt[people[i].second]++;
        for (int i = 1; i <= pcnt; i++)
            if (cnt[people[i].second] >= stock)
                cnt[people[i].second]--, pans += people[i].first, tag[i] = true, rem++;
        if (rem >= stock)
            gans = min(gans, pans);
        else
        {
            for (int i = 1; i <= pcnt && rem < stock; i++)
                if (!tag[i])
                    cnt[people[i].second]--, pans += people[i].first, tag[i] = true, rem++;
            gans = min(gans, pans);
        }
    }
    printf("%lld\n", gans);
    return 0;
}