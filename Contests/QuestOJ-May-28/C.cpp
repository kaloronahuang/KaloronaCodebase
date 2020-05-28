// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220;

int T, n, K, ai[MAX_N], tmp[MAX_N];
set<vector<int> /**/> st;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        st.clear();
        scanf("%d%d", &n, &K);
        vector<int> G;
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]), G.push_back(ai[i]);
        sort(ai + 1, ai + 1 + n), sort(G.begin(), G.end());
        st.insert(G);
        for (int minute = 1; minute <= K; minute++)
            for (int stat = 0; stat < (1 << minute); stat++)
            {
                bool flag = true;
                for (int i = 1; i <= n && flag; i++)
                {
                    tmp[i] = ai[i];
                    for (int j = 0; j < minute && flag; j++)
                        if (stat & (1 << j))
                            tmp[i] >>= 1;
                        else
                        {
                            if (tmp[i] == 0)
                                flag = false;
                            tmp[i] -= 1;
                        }
                }
                if (flag)
                {
                    vector<int> v;
                    for (int i = 1; i <= n; i++)
                        v.push_back(tmp[i]);
                    st.insert(v);
                }
            }
        printf("%lld\n", 1LL * st.size());
    }
    return 0;
}