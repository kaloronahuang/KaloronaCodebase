// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, A, B, C, D;
char S[MAX_N];

int main()
{
	scanf("%d%d%d%d%d%s", &n, &A, &B, &C, &D, S + 1);
	// judge the blocks;
	bool ans = true;
	ans &= (S[A] == '.' && S[B] == '.' && S[C] == '.' && S[D] == '.');
	int cnt = 0;
	for (int i = A; i <= C; i++)
		cnt += S[i] == '#', cnt = (S[i] == '.' ? 0 : cnt), ans &= cnt <= 1;
	cnt = 0;
	for (int i = B; i <= D; i++)
		cnt += S[i] == '#', cnt = (S[i] == '.' ? 0 : cnt), ans &= cnt <= 1;
	// if intersect;
	int l = max(A, B), r = min(C, D);
	if (A <= B && D <= C)
	{
		bool verdict = false;
		if (A < B && S[l - 1] == '.')
			cnt++;
		for (int i = l; i <= r; i++)
			cnt += S[i] == '.', cnt = (S[i] == '#' ? 0 : cnt), verdict |= cnt >= 3;
		if (cnt == 2 && D < C && S[r + 1] == '.')
			verdict |= true;
		ans &= verdict;
	}
	puts(ans ? "Yes" : "No");
	return 0;
}
