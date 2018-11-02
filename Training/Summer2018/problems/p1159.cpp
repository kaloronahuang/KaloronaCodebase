// p1159;
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

struct stuff
{
    int v;
    int c;
};

bool comp(stuff a, stuff b)
{
    return (a.v > b.v);
}

int main()
{
    int N, T;
    cin >> N >> T;
    stuff pack[T];
    for (int i = 0; i < T; i++)
        cin >> pack[i].v >> pack[i].c;
    int table[T + 1][N + 1];
    memset(table, 0, sizeof(table));
    sort(pack, pack + T, comp);
    for (int i = 1; i < T + 1; i++)
        for (int j = N; j > -1; j--)
            if (j >= pack[i - 1].v)
                table[i][j] = max(table[i - 1][j],
                                  table[i-1][j - pack[i - 1].v] + pack[i - 1].c);
            else
                table[i][j] = table[i - 1][j];
    cout << table[T][N];
} // p1159;