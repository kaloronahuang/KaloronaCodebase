// CH2907.cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
#define pr pair<int, int>
using namespace std;
const int maxn = 120;
int dx[8] = {-1, -1, -1, 1, 1, 1, 0, 0};
int dy[8] = {-1, 0, 1, -1, 0, 1, -1, 1};
int N, M, mx, my, stat[maxn][maxn];
char map[maxn][maxn];
bool vis[maxn][maxn];
bool validiate(pr x)
{
	return x.first > 0 && x.first <= N && x.second > 0 && x.second <= M && !vis[x.first][x.second];
}
bool check()
{
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			if (!vis[i][j])
				return false;
	return true;
}
void bfs()
{
	queue<pr> ps;
	ps.push(make_pair(mx, my));
	stat[mx][my] = 0;
	while (!ps.empty())
	{
		pr curt = ps.front();
		ps.pop();
		for (int i = 0; i < 8; i++)
		{
			pr neo = make_pair(curt.first + dx[i], curt.second + dy[i]);
			if (validiate(neo))
			{
				ps.push(neo);
				vis[neo.first][neo.second] = true;
				stat[neo.first][neo.second] = stat[curt.first][curt.second] + 1;
			}
		}
		if (check())
		{
			printf("%d", stat[curt.first][curt.second] + 1);
			return;
		}
	}
}
int main()
{
	scanf("%d%d%d%d", &M, &N, &my, &mx);
	for (int i = N; i >= 1; i--)
		scanf("%s", map[i] + 1);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			if (map[i][j] == '*')
				vis[i][j] = true;
	bfs();
	return 0;
}