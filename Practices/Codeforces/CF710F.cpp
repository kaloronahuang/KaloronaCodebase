// CF710F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, LOG = 30;

int q, mtot[2], limit, ptot;
char cmdlet[MAX_N];

struct node
{
	int ch[26], vson[26], fail, tag, sum;
} nodes[MAX_N];

struct AC_Automaton
{
	int siz, root;
	
	void insert(char *str)
	{
		int p = root;
		for (int i = 1; str[i]; i++)
		{
			if (nodes[p].ch[str[i] - 'a'] == 0)
				nodes[p].ch[str[i] - 'a'] = nodes[p].vson[str[i] - 'a'] = ++ptot;
			p = nodes[p].ch[str[i] - 'a'];
		}
		nodes[p].tag++;
	}
	
	void clear(int u)
	{
		memcpy(nodes[u].vson, nodes[u].ch, sizeof(nodes[u].ch));
		for (int i = 0; i < 26; i++)
			if (nodes[u].ch[i])
				clear(nodes[u].ch[i]);
	}
	
	void build()
	{
		clear(root);
		queue<int> q;
		nodes[root].sum = nodes[root].tag;
		for (int i = 0; i < 26; i++)
			if (nodes[root].ch[i])
				nodes[nodes[root].ch[i]].fail = root, q.push(nodes[root].ch[i]);
			else
				nodes[root].vson[i] = root;
		while (!q.empty())
		{
			int u = q.front();
			q.pop(), nodes[u].sum = nodes[nodes[u].fail].sum + nodes[u].tag;
			for (int i = 0; i < 26; i++)
				if (nodes[u].ch[i])
				{
					nodes[nodes[u].ch[i]].fail = nodes[nodes[u].fail].vson[i];
					q.push(nodes[u].ch[i]);
				}
				else
					nodes[u].vson[i] = nodes[nodes[u].fail].vson[i];
		}
	}
	
	int query(char *str)
	{
		int p = root, ret = 0;
		for (int i = 1; str[i]; i++)
			p = nodes[p].vson[str[i] - 'a'], ret += nodes[p].sum;
		return ret;
	}
	
} tr[2][LOG];

int merge(int x, int y)
{
	if (x == 0 || y == 0)
		return x + y;
	nodes[x].tag += nodes[y].tag;
	for (int i = 0; i < 26; i++)
		nodes[x].ch[i] = merge(nodes[x].ch[i], nodes[y].ch[i]);
	return x;
}

void insert(int idx, char *str)
{
	mtot[idx]++;
	tr[idx][mtot[idx]].root = ++ptot;
	tr[idx][mtot[idx]].siz = 1;
	tr[idx][mtot[idx]].insert(str);
	while (mtot[idx] > 1 && tr[idx][mtot[idx]].siz == tr[idx][mtot[idx] - 1].siz)
		mtot[idx]--, tr[idx][mtot[idx]].siz += tr[idx][mtot[idx] + 1].siz, tr[idx][mtot[idx]].root = merge(tr[idx][mtot[idx]].root, tr[idx][mtot[idx] + 1].root);
	tr[idx][mtot[idx]].build();
}

int query(int idx, char *str)
{
	int ret = 0;
	for (int i = 1; i <= mtot[idx]; i++)
		ret += tr[idx][i].query(str);
	return ret;
}

int main()
{
	scanf("%d", &q);
	while (q--)
	{
		int opt;
		scanf("%d%s", &opt, cmdlet + 1);
		if (opt == 1)
			insert(0, cmdlet);
		else if (opt == 2)
			insert(1, cmdlet);
		else
			printf("%d\n", query(0, cmdlet) - query(1, cmdlet));
		fflush(stdout);
	}
	return 0;
}
