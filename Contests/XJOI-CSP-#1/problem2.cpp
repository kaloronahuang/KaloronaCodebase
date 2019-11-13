// problem2.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int tag[MAX_N], n, m;
deque<int> qs[MAX_N];

int main()
{
    freopen("problem2.in", "r", stdin);
    freopen("problem2.out", "w", stdout);
    scanf("%d%d", &n, &m);
    if (n <= 1000 && m <= 1000)
        while (m--)
        {
            int opt, x, y;
            scanf("%d", &opt);
            if (opt == 1)
                scanf("%d%d", &x, &y), qs[x].push_front(y);
            else if (opt == 2)
                scanf("%d", &x), printf("%d\n", qs[x].front()), qs[x].pop_front();
            else if (opt == 3)
                scanf("%d%d", &x, &y), qs[x].push_back(y);
            else if (opt == 4)
                scanf("%d", &x), printf("%d\n", qs[x].back()), qs[x].pop_back();
            else if (opt == 5)
            {
                scanf("%d%d", &x, &y);
                for (deque<int>::iterator it = qs[x].begin(); it != qs[x].end(); it++)
                    (*it) = ((*it) + y) % mod;
            }
            else
            {
                scanf("%d%d", &x, &y);
                for (deque<int>::iterator it = qs[y].begin(); it != qs[y].end(); it++)
                    qs[x].push_back(*it);
                qs[y].clear();
            }
        }
    else
        while (m--)
        {
            int opt, x, y;
            scanf("%d", &opt);
            if (opt == 1)
                scanf("%d%d", &x, &y), qs[x].push_front((y + mod - tag[x]) % mod);
            else if (opt == 2)
                scanf("%d", &x), printf("%d\n", (qs[x].front() + tag[x]) % mod), qs[x].pop_front();
            else if (opt == 3)
                scanf("%d%d", &x, &y), qs[x].push_back((y + mod - tag[x]) % mod);
            else if (opt == 4)
                scanf("%d", &x), printf("%d\n", (qs[x].back() + tag[x]) % mod), qs[x].pop_back();
            else if (opt == 5)
            {
                scanf("%d%d", &x, &y);
                tag[x] = (tag[x] + y) % mod;
            }
            else
            {
                scanf("%d%d", &x, &y);
                for (deque<int>::iterator it = qs[y].begin(); it != qs[y].end(); it++)
                    qs[x].push_back(((*it) + tag[y] - tag[x] + mod) % mod);
                qs[y].clear(), tag[y] = 0;
            }
        }

    return 0;
}