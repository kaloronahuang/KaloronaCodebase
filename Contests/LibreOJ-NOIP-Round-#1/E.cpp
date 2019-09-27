// E.cpp
#include <bits/stdc++.h>

namespace IO
{
int c;
unsigned int seed;
unsigned int randnum()
{
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

inline int read(int &x)
{
    scanf("%d", &x);
    return x;
}
inline void init_case(int &m, int &a, int &b, int &d, int p[])
{
    scanf("%d%u%d%d%d%d", &m, &seed, &a, &b, &c, &d);
    for (int i = 1; i <= m; i++)
    {
        if (randnum() % c == 0)
            p[i] = -1;
        else
            p[i] = randnum() % b;
    }
}

inline void update_ans(unsigned int &ans_sum, unsigned int cur_ans, int no)
{
    const static unsigned int mod = 998244353;
    ans_sum ^= (long long)no * (no + 7) % mod * cur_ans % mod;
}
} // namespace IO
using IO::init_case;
using IO::read;
using IO::update_ans;

using namespace std;

const int MAX_N = 2000005, MAX_C = 1e7 + 200;
bool vis[MAX_C], out[MAX_C];
int head, tail, q[MAX_C];
deque<int> dq;

int main()
{
    static int pi[MAX_N];
    int T;
    read(T);
    int m, a, b, d;
    while (T--)
    {
        unsigned int ans_sum = 0, cur_ans = 0;
        init_case(m, a, b, d, pi);
        memset(q, 0, sizeof(q));
        memset(vis, false, sizeof(vis));
        memset(out, false, sizeof(out));
        while (!dq.empty())
            dq.pop_back();
        head = 1, tail = 0;
        for (int i = 1; i <= a + 1; i++)
            vis[i] = true;
        int ncur = 0;
        while (vis[ncur + 1])
            ncur++;
        for (int i = 1; i <= m; i++)
        {
            pi[i]++;
            if (pi[i] == 0)
            {
                if (d == 1 || dq.empty())
                    continue;
                else
                {
                    out[dq.front()] = false;
                    if (dq.front() == q[head])
                        head++;
                    dq.pop_front();
                }
            }
            else if (!vis[pi[i]])
            {
                // buy;
                vis[pi[i]] = true;
                // try to expand;
                while (vis[ncur + 1])
                    ncur++;
            }
            else if (vis[pi[i]] && !out[pi[i]])
            {
                // drop it!
                if (d == 1)
                    continue;
                dq.push_back(pi[i]), out[pi[i]] = true;
                while (head <= tail && q[tail] >= pi[i])
                    tail--;
                q[++tail] = pi[i];
            }
            else
            {
                // recover at last;
                if (d == 1 || dq.empty())
                    continue;
                else
                {
                    out[dq.front()] = false;
                    if (dq.front() == q[head])
                        head++;
                    dq.pop_front();
                }
            }
            cur_ans = ncur;
            if (head <= tail)
                cur_ans = min(cur_ans, ((unsigned int)(q[head] - 1)));
            update_ans(ans_sum, cur_ans, i);
        }
        printf("%u\n", ans_sum);
    }
    return 0;
}