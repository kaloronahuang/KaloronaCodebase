// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int n, m;

struct watchpoint
{
    ll t, x, y;
    bool operator<(const watchpoint &rhs) const { return t < rhs.t; }
} pts[MAX_N];

char decode(int x) { return x == 0 ? 'U' : (x == 1 ? 'D' : (x == 2 ? 'L' : 'R')); }

namespace Subtask1
{

    pair<ll, ll> vecs[MAX_N];

    int handler()
    {
        for (int stat = 0; stat < (1 << (m << 1)); stat++)
        {
            string str;
            for (int i = 0; i < (m << 1); i += 2)
                str += decode((stat >> i) & 3);
            int cx = 0, cy = 0;
            vecs[0] = make_pair(cx, cy);
            for (int i = 1; i <= m; i++)
                if (str[i - 1] == 'U')
                    vecs[i] = make_pair(0, 1);
                else if (str[i - 1] == 'D')
                    vecs[i] = make_pair(0, -1);
                else if (str[i - 1] == 'L')
                    vecs[i] = make_pair(-1, 0);
                else
                    vecs[i] = make_pair(1, 0);
            for (int i = 1; i <= m; i++)
                vecs[i].first += vecs[i - 1].first, vecs[i].second += vecs[i - 1].second;
            bool flag = true;
            for (int i = 1; i <= n; i++)
            {
                ll loop_num = pts[i].t / m, loop_rem = pts[i].t % m;
                ll sx = vecs[n].first * loop_num + vecs[loop_rem].first;
                ll sy = vecs[n].second * loop_num + vecs[loop_rem].second;
                if (sx != pts[i].x || sy != pts[i].y)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                cout << str << endl, exit(0);
        }
        puts("NO");
        return 0;
    }

} // namespace Subtask1

namespace Subtask2
{
    // t \leq m;
    int handler()
    {
        int cx = 0, cy = 0, ct = 0;
        string str;
        for (int i = 1; i <= n; i++)
        {
            int deltaX = abs(pts[i].x - cx), deltaY = abs(pts[i].y - cy), rem = pts[i].t - ct - deltaX - deltaY;
            if (deltaX + deltaY > pts[i].t - ct || ((pts[i].t - ct - (deltaX + deltaY)) % 2 != 0))
                puts("NO"), exit(0);
            while (deltaX--)
                str += pts[i].x - cx > 0 ? 'R' : 'L';
            while (deltaY--)
                str += pts[i].y - cy > 0 ? 'U' : 'D';
            while (rem)
                str += "UD", rem -= 2;
            cx = pts[i].x, cy = pts[i].y, ct = pts[i].t;
        }
        cout << str << endl;
        return 0;
    }

} // namespace Subtask2

namespace Subtask3
{
    // y_i == 0;
    int handler()
    {
        int cx = 0, cy = 0, ct = 0;
        string str;
        for (int i = 1; i <= n; i++)
        {
            int deltaX = abs(pts[i].x - cx), deltaY = abs(pts[i].y - cy);
            if (deltaX + deltaY > pts[i].t || ((pts[i].t - deltaX + deltaY) % 2 != 0))
                puts("NO"), exit(0);
        }
    }

} // namespace Subtask3

int main()
{
    scanf("%d%d", &n, &m);
    bool flag2 = true, flag3 = true;
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld%lld", &pts[i].t, &pts[i].x, &pts[i].y), flag3 &= pts[i].y == 0, flag2 &= pts[i].t <= m;
    // sort(pts + 1, pts + 1 + n);
    if (m <= 10)
        return Subtask1::handler();
    else if (flag2 && n <= 1e5 && m <= 1e6)
        return Subtask2::handler();
    else if (flag3 && n <= 1e5 && m <= 1e6)
        return Subtask3::handler();
    else
        puts("NO");
    return 0;
}