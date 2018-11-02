// P1131.cpp
#include <iostream>

using namespace std;

const int maxn = 500010;
#define ll long long
int point[maxn];
int next[maxn];
int weight[maxn];
int to[maxn];
int n, s;
int current = 0;
ll max_dis = 0;
ll ans_base = 0;

void Add_edge(int src, int dst, int w)
{
    next[current] = point[src];
    to[current] = dst;
    point[src] = current;
    weight[current] = w;
    current++;
}

void DFS_dis(int curt, int fat, int sum)
{
    bool flag = true;
    for (int i = point[curt]; i != -1; i = next[i])
        if (to[i] != fat)
            flag = false, DFS_dis(to[i], curt, sum + weight[i]);
    if (flag)
        max_dis = max(max_dis, (ll)sum);
}

ll DFS_ans(int curt, int fat, int sum)
{
    ll arr[20];
    bool flag = true;
    ll max_val = 0;
    int cur = 0;
    for (int i = point[curt]; i != -1; i = next[i])
    {
        int jto = to[i];
        if (jto == fat)
            continue;
        flag = false;
        ll leng = DFS_ans(jto, curt, sum + weight[i]);
        arr[cur] = leng;
        max_val = max(max_val, arr[cur++]);
    }
    if (flag)
        return sum;
    for (int i = 0; i < cur; i++)
        ans_base += (max_val - arr[i]);
    return max_val;
}

int main()
{
    cin >> n >> s;
    fill(point, point + n + 10, -1);
    fill(next, next + n + 10, -1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b, t;
        cin >> a >> b >> t;
        Add_edge(a, b, t), Add_edge(b, a, t);
    }
    DFS_dis(s, 0, 0);   
    DFS_ans(s, 0, 0);
    cout << ans_base;
    return 0;
}