// POJ3263.cpp
#include <iostream>
#include <map>
using namespace std;
const int maxn = 10020;
int calc[maxn], N, I, H, R, hei[maxn];
map<pair<int, int>, bool> vis;
int main()
{
    cin >> N >> I >> H >> R;
    for (int i = 0; i < R; i++)
    {
        int x, y;
        cin >> x >> y;
        if (x > y)
            swap(x, y);
        if (vis[make_pair(x, y)])
            continue;
        vis[make_pair(x, y)] = true;
        calc[x + 1]--;
        calc[y]++;
    }
    for (int i = 1; i <= N; i++)
        hei[i] = hei[i - 1] + calc[i], cout << hei[i] + H << endl;
    return 0;
}