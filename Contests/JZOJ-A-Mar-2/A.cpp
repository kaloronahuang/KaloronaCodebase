// A.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>
using namespace std;
const int MAX_N = 1001000;
pr prs[MAX_N];
int n, m, si, sj;
int answer, exitI, exitJ;
int main()
{
    answer = 0x3f3f3f3f;
    scanf("%d%d%d%d", &m, &n, &si, &sj);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &prs[i].first, &prs[i].second);
    sort(prs + 1, prs + 1 + n);
    for (int i = 1; i <= n; i++)
    {
        pr pta = prs[i], ptb = make_pair(si, sj);
        if (pta.first < ptb.first)
            swap(pta, ptb);
        int jl = ptb.second, jr = ptb.second + (pta.first - ptb.first) * 2;
        int ans = (pta.first - ptb.first) << 1;
        if (pta.second >= jl && pta.second <= jr &&
            (ans < answer || (ans == answer && exitJ >= prs[i].second)))
        {
            answer = ans, exitI = prs[i].first, exitJ = prs[i].second;
            if ((pta.second & 1) != (ptb.second & 1))
                answer -= 1;
            continue;
        }
        ans += min(abs(pta.second - jl), abs(pta.second - jr));
        if (ans < answer || (ans == answer && exitJ >= prs[i].second))
            answer = ans, exitI = prs[i].first, exitJ = prs[i].second;
    }
    printf("%d %d\n%d", exitI, exitJ, answer + 1);
    return 0;
}