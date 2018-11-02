// P1135.cpp
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int N, A, B;
int seq[500];
const int INF = 0x7fffffff;
int depth[500];

int BFS()
{
    queue<int> levels;
    levels.push(A);
    while (!levels.empty())
    {
        int curt = levels.front();
        levels.pop();
        if (curt == B)
            return depth[curt];
        if (curt + seq[curt] <= N && depth[curt + seq[curt]] > depth[curt] + 1)
            levels.push(curt + seq[curt]), depth[curt + seq[curt]] = depth[curt] + 1;
        if (curt - seq[curt] > 0 && depth[curt - seq[curt]] > depth[curt] + 1)
            levels.push(curt - seq[curt]), depth[curt - seq[curt]] = depth[curt] + 1;
    }
    return -1;
}

int main()
{
    fill(depth, depth + 500, INF);
    cin >> N >> A >> B;
    depth[A] = 0;
    for (int i = 1; i <= N; i++)
        cin >> seq[i];
    cout << BFS();
    return 0;
}