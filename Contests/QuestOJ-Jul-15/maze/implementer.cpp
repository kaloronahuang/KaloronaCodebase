#include "grader.h"
#include <bits/stdc++.h>

static const int MAXN = 1000005;

static void wrong(const char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

static void wrong(const char *msg, int x)
{
	printf(msg, x);
	printf("\n");
	exit(0);
}

static int initialDeep, T, randSeed, path[MAXN];

static void init()
{
	scanf("%d%d%d", &initialDeep, &T, &randSeed);
	srand(randSeed);
	int lastColor = rand() % 3;
	for (int i = 1; i <= initialDeep; i++)
		lastColor = path[++path[0]] = (lastColor + rand() % 2 + 1) % 3;
}

static int cntMoveCalls = 0, cntQueryCalls = 0;

bool move(int color)
{
	if (++cntMoveCalls > 1000000)
		wrong("move: too many calls");
	if (path[0] == 0)
		wrong("already out of the maze");
	if (color < 0 || color > 2)
		wrong("move: argument color (%d) not in [0, 2]", color);
	if (color == path[path[0]]) path[0]--;
	else path[++path[0]] = color;
	return path[0] == 0;
}

int query()
{
	if (++cntQueryCalls > T)
		wrong("query: too many calls");
	return path[0];
}

static void check()
{
	if (path[0] != 0)
		wrong("still in the maze %d\n", path[0]);
	printf("Correct\n");
	printf("# of move calls = %d\n", cntMoveCalls);
	printf("# of query calls = %d\n", cntQueryCalls);
}

int main()
{
	/*
	freopen("maze.in","r",stdin);
	freopen("maze.out","w",stdout);
	*/
	init();
	findpath(initialDeep, T);
	check();
}

