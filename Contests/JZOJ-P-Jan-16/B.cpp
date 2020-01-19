// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 160;
typedef deque<int> dq;

int n, ai[MAX_N][MAX_N], pcnt;

void fileIO()
{
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
}

bool dfs(int pos, vector<dq> st)
{
    bool flag1 = true, flag2 = false;
    // find an empty {x};
    int cnt = 0;
    for (int i = 0, siz = st.size(); i < siz; i++)
    {
        dq curt = st[i];
        int min_val = 0x3f3f3f3f;
        for (int j = 0, siz_ = curt.size(); j < siz_; j++)
            min_val = min(min_val, curt[j]);
        if (min_val == 0)
            continue;
        cnt++;
        for (int stat = 0; stat < (1 << curt.size()); stat++)
        {
            vector<dq> nxt = st;
            st.erase(st.begin() + i);
            bool flag = false;
            dq tmp;
            for (int j = 0; j < curt.size(); j++)
            {
                int cbit = ((stat >> j) & 1);
                if (cbit >= curt[j])
                {
                    flag = true;
                    break;
                }
                tmp.push_back(cbit);
            }
            if (flag)
                continue;
            for (int sub = 1; sub < (1 << curt.size()); sub++)
            {
                dq tp;
                for (int j = 0; j < curt.size(); j++)
                    if (sub & (1 << j))
                        tp.push_back(curt[j]);
                    else
                        tp.push_back(tmp[j]);
                nxt.push_back(tp);
            }
            bool res = dfs(pos + 1, nxt);
            flag1 |= res, flag2 &= res;
        }
    }
    if (cnt == 0)
        return (pos & 1);
    if (pos & 1)
        return flag2;
    else
        return flag1;
}

int main()
{
    fileIO();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &ai[i][j]);
    vector<int> curt;
    vector<dq> init;
    for (int i = 1; i <= n; i++)
        curt.push_back(i);
    do
    {
        dq str;
        for (int i = 1; i <= n; i++)
            str.push_back(ai[i][curt[i - 1]]);
        init.push_back(str);
    } while (next_permutation(curt.begin(), curt.end()));
    if (dfs(0, init))
        puts("xiaoDyingle");
    else
        puts("xiaoDwandanle");
    return 0;
}