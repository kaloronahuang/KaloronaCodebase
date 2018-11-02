// P1065.cpp
#include <iostream>
#include <queue>

using namespace std;

int m, n;
int order[500];
int machineID[30][30];
int machineTime[30][30];
int orderTime[30];
int lineTime[30];
bool timeline[30][2000];
struct task
{
    int pcs_id, pcs_idx, machine, tim;
};

int ans = 0;

bool check(int maid, int st, int ed)
{
    for (int i = st; i <= ed; i++)
        if (timeline[maid][i])
            return false;
    return true;
}

void solve()
{
    queue<task> ts;
    for (int i = 1; i <= m * n; i++)
        ts.push(task{
            order[i],
            ++orderTime[order[i]],
            machineID[order[i]][orderTime[order[i]]],
            machineTime[order[i]][orderTime[order[i]]]});
    while (!ts.empty())
    {
        task curt = ts.front();
        ts.pop();
        for (int i = lineTime[curt.pcs_id];; i++)
        {
            if (check(curt.machine, i, i + curt.tim-1))
            {
                for (int j = i; j < i + curt.tim; j++)
                    timeline[curt.machine][j] = true;
                ans = max(ans, i + curt.tim);
                lineTime[curt.pcs_id] = i + curt.tim;
                break;
            }
        }
    }
    cout << ans;
}

int main()
{
    cin >> m >> n;
    for (int i = 1; i <= m * n; i++)
        cin >> order[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> machineID[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> machineTime[i][j];
    solve();
    return 0;
}