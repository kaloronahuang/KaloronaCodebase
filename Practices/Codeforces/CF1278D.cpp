// CF1278D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int n, m, fa[MAX_N];
pair<int, int> segs[MAX_N], pts[MAX_N << 1];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &segs[i].first, &segs[i].second);
        pts[(i << 1) - 1] = make_pair(segs[i].first, i);
        pts[(i << 1)] = make_pair(segs[i].second, i);
        fa[i] = i;
    }
    sort(pts + 1, pts + 1 + (n << 1));
    set<pair<int, int> /**/> st;
    for (int i = 1; i <= (n << 1) && m <= n - 1; i++)
    {
        if (st.count(pts[i]))
            st.erase(pts[i]);
        else
        {
            int idx = pts[i].second, r = segs[idx].second;
            for (set<pair<int, int> /**/>::iterator it = st.begin(); it != st.end(); it++)
            {
                if (it->first > r)
                    break;
                int target = it->second;
                fa[find(idx)] = find(target), m++;
                if (m > n - 1)
                    break;
            }
            st.insert(make_pair(segs[idx].second, idx));
        }
    }
    int components = 0;
    for (int i = 1; i <= n; i++)
        components += (find(i) == i);
    if (components == 1 && m == n - 1)
        puts("YES");
    else
        puts("NO");
    return 0;
}