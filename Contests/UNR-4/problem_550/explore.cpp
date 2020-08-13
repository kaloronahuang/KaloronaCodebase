// explore.cpp
#include <bits/stdc++.h>
#include "explore.h"

typedef unsigned long long ull;

using namespace std;

int n, m;

void Subtask1()
{
	vector<ull> A, ret;
	for (int i = 1; i <= n; i++)
		A.push_back(1LL << (i - 1));
	vector<int> S;
	for (int i = 1; i <= m; i++)
		S.push_back(i);
	ret = Query(A, S);
	for (int i = 1; i <= n; i++)
	{
		ull bi = ret[i - 1];
		// cerr << bi << endl;
		for (int j = i + 1; j <= n; j++)
			if (bi & (1LL << (j - 1)))
				Report(i, j);
	}
}

void Subtask2()
{
	vector<ull> A, ret;
	vector<int> S;
	for (int i = 1; i <= m; i++)
		S.push_back(i);
	for (int i = 1; i <= n; i += 60)
	{
		A.clear(), A.resize(n, 0);
		for (int j = i; j < i + 60; j++)
			A[j - 1] = (1LL << (j - i));
		ret = Query(A, S);
		for (int j = 1; j <= n; j++)
			for (int k = i; k < i + 60; k++)
				if (ret[j - 1] & (1LL << (k - i)) && j < k)
					Report(j, k);
	}
}

void Solve(int N, int M)
{
	n = N, m = M;
	if (n <= 60)
		return (void)(Subtask1());
	else if (n == 3000)
		return (void)(Subtask2());
}
