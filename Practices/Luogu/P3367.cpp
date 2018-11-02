// P3367.cpp
#include <iostream>

using namespace std;

int n, m;
const int maxn = 10010;
int sequence[maxn];

int find(int idx)
{
    if (sequence[idx] != idx)
        sequence[idx] = find(sequence[idx]);
    return sequence[idx];
}

void unionfy(int a, int b)
{
    if (find(a) != find(b))
        sequence[find(a)] = find(b);
}

void init()
{
    cin >> n >> m;
    for (int i = 0; i < n + 1; i++)
        sequence[i] = i;
}

void process()
{
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        cin >> z >> x >> y;
        if (z == 1)
            unionfy(x, y);
        else if (find(x) == find(y))
            cout << "Y" << endl;
        else
            cout << "N" << endl;
    }
}

int main()
{
    init();
    process();
    return 0;
}