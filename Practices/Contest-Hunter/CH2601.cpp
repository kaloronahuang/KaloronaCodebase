// CH2601.cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 510;
int T, N, M;
bool map[maxn][maxn];
int dist[maxn][maxn];
char ch;
int convert(int x, int y) { return x * N + y; }
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &N, &M);
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
                cin >> ch, map[i][j] = (ch == '\\');
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
                dist[i]
    }
    return 0;
}