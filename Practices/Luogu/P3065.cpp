// P3065.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, ch[MAX_N][26], ptot = 1, deg[26], tag[MAX_N];
string org[MAX_N];
vector<int> G[26];

void insert(string &str)
{
	int p = 1;
	for (char c : str)
	{
		if (ch[p][c - 'a'] == 0)
			ch[p][c - 'a'] = ++ptot;
		p = ch[p][c - 'a'];
	}
	tag[p]++;
}

void dfs(int u)
{
	for (int i = 0; i < 26; i++)
		if (ch[u][i])
			tag[ch[u][i]] += tag[u], dfs(ch[u][i]);
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> org[i], insert(org[i]);
	dfs(1);
	vector<int> ansBox;
	for (int i = 1; i <= n; i++)
	{
		for (int c = 0; c < 26; c++)
			G[c].clear(), deg[c] = 0;
		int p = 1;
		for (char c : org[i])
		{
			for (int gc = 0; gc < 26; gc++)
				if (c - 'a' != gc && ch[p][gc])
					G[c - 'a'].push_back(gc), deg[gc]++;
			p = ch[p][c - 'a'];
		}
		queue<int> q;
		for (int i = 0; i < 26; i++)
			if (deg[i] == 0)
				q.push(i);
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (int v : G[u])
				if (--deg[v] == 0)
					q.push(v);
		}
		if (*max_element(deg, deg + 26) == 0 && tag[p] == 1)
			ansBox.push_back(i);
	}
	printf("%lld\n", 1LL * ansBox.size());
	for (int x : ansBox)
		cout << org[x] << endl;
	return 0;
}
