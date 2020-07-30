// subway.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, m;

struct segment
{
    int s, t;
} segs[MAX_N];

int main()
{
    freopen("subway.in", "r", stdin);
    freopen("subway.out", "w", stdout);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &segs[i].s, &segs[i].t);
        if (n == 2)
        {
            int s1 = segs[1].s, t1 = segs[1].t;
            int s2 = segs[2].s, t2 = segs[2].t;
            int l1 = min(s1, t1), r1 = max(s1, t1);
            int l2 = min(s2, t2), r2 = max(s2, t2);
            bool rev = (s1 < t1) ^ (s2 < t2);
            if (rev == 0)
            {
                printf("%d 2\n", abs(t1 - s1) + abs(t2 - s2));
                for (int i = 1; i <= 2; i++)
                    printf("0 %d %d\n", i, segs[i].t);
            }
            else
            {
                printf("%d\n", min(abs(t1 - s1) + abs(t2 - s2), abs(t1 - s2) + abs(t2 - s1)));
                if (abs(t1 - s1) + abs(t2 - s2) <= abs(t1 - s2) + abs(t2 - s1))
                    for (int i = 1; i <= 2; i++)
                        printf("0 %d %d\n", i, segs[i].t);
                else
                {
                    for (int i = 1; i <= 2; i++)
                        printf("0 %d %d\n", i, segs[1].t);
                    printf("1 1 2\n");
                    printf("0 2 %d\n", segs[2].t);
                }
            }
            continue;
        }
    }
    return 0;
}