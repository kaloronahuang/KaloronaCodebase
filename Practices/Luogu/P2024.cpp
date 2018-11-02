// P2024.cpp
#include <iostream>

using namespace std;

int maxn = 500010;
struct UnionFindSet
{
	int mem[maxn];

	int Find(int u)
	{
		if(mem[u] == u)
			return u;
		return mem[u] = Find(mem[u]);
	}
	
	void Unionfy(int a, int b)
	{
		if(Find(a)!=Find(b))
			mem[Find(a)] = b;
	}
	
	UnionFindSet()
	{
		for(int i = 0;i<maxn;i++)
			mem[i] i;
	}
}

struct edge
{
	edge *next;
	int to;
} es[500010];
