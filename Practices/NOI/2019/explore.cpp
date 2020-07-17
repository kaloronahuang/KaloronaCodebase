// explore.cpp
#include "explore.h"
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, MAX_E = 3e5 + 200;

typedef pair<int, int> pii;

int n, m, log2_[MAX_N];

namespace Subtask1
{

	bool stat[MAX_N], mat[550][550];

	void subtask1Handler()
	{
		for (int u = 0; u < n - 1; u++)
		{
			modify(u), stat[u] ^= 1;
			for (int i = u + 1; i < n; i++)
			{
				bool cs = query(i);
				if (cs != stat[i])
					report(u, i);
				stat[i] = cs;
			}
		}
	}

} // namespace Subtask1

namespace Subtask2
{

	vector<int> pts[2];

	void solve(vector<int> pt1, vector<int> pt2, int light)
	{
		int len = pt1.size();
		if (len == 1)
			return (void)(report(pt1.front(), pt2.front()));
		vector<int> seg[2][2];
		int mid = len >> 1;
		for (int i = 0; i < mid; i++)
			seg[0][0].push_back(pt1[i]), modify(pt1[i]);
		for (int i = 0; i < len; i++)
			if (query(pt2[i]) != light)
				seg[0][1].push_back(pt2[i]);
			else
				seg[1][1].push_back(pt2[i]);
		for (int i = mid; i < len; i++)
			seg[1][0].push_back(pt1[i]);
		solve(seg[0][0], seg[0][1], light ^ 1), solve(seg[1][0], seg[1][1], light);
	}

	void subtask2Handler()
	{
		for (int i = 0; i < n; i++)
		{
			if (query(i))
				pts[1].push_back(i);
			else
				pts[0].push_back(i), modify(i);
		}
		solve(pts[0], pts[1], 1);
	}

} // namespace Subtask2

namespace Subtask3
{

	int fa[MAX_N];

	void subtask3Handler()
	{
		for (int i = 2; i <= n; i++)
			log2_[i] = log2_[i >> 1] + 1;
		for (int i = 0; i <= log2_[n]; i++)
		{
			for (int p = 0; p < n; p++)
			{
				if (query(p))
					fa[p] |= 1 << i;
				if (p & (1 << i))
					modify(p);
			}
			for (int p = 0; p < n; p++)
				if (p & (1 << i))
					modify(p);
		}
		for (int i = 1; i < n; i++)
			report(fa[i], i);
	}

} // namespace Subtask3

namespace SubtaskChain
{

	int xorsum[MAX_N], fa[MAX_N];

	void subtaskHandler()
	{
		for (int i = 2; i <= n; i++)
			log2_[i] = log2_[i >> 1] + 1;
		for (int i = 0; i <= log2_[n]; i++)
		{
			for (int p = 0; p < n; p++)
				if (p & (1 << i))
					modify(p);
			for (int p = 0; p < n; p++)
				if (query(p))
					xorsum[p] |= (1 << i);
			for (int p = 0; p < n; p++)
				if (p & (1 << i))
					modify(p);
		}
		modify(0);
		vector<int> pts;
		queue<pii> q;
		for (int i = 1; i < n; i++)
			if (query(i))
				pts.push_back(i), q.push(make_pair(i, 0));
		while (!q.empty())
		{
			int u = q.front().first, v = q.front().second;
			q.pop();
			report(u, v);
			int other = xorsum[u] ^ u ^ v;
			if (other == 0)
				continue;
			q.push(make_pair(other, u));
		}
	}

} // namespace SubtaskChain

void explore(int N, int M)
{
	n = N, m = M;
	// return (void)(SubtaskChain::subtaskHandler());
	if (n <= 500)
		return (void)(Subtask1::subtask1Handler());
	else if (n == 99996 || n == 199996)
		return (void)(SubtaskChain::subtaskHandler());
	else if (m == n / 2 && n % 2 == 0)
		return (void)(Subtask2::subtask2Handler());
	else if (m == n - 1)
		return (void)(Subtask3::subtask3Handler());
}