// CF1161B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef pair<int, int> pii;

int n, m, ai[MAX_N], bi[MAX_N];
set<pii> st;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &ai[i], &bi[i]), st.insert(make_pair(min(ai[i], bi[i]), max(ai[i], bi[i])));
    for (int i = 1; i <= (n >> 1); i++)
        if (n % i == 0)
        {
            bool flag = true;
            for (auto x : st)
            {
                int u = (x.first + i - 1) % n + 1, v = (x.second + i - 1) % n + 1;
                flag &= st.count(make_pair(min(u, v), max(u, v)));
            }
            if (flag)
                puts("Yes"), exit(0);
        }
    puts("No");
    return 0;
}