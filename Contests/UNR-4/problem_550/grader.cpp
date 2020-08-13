#include <bits/stdc++.h>
#include "explore.h"


const int MAX_N = 5e5 + 10;
const int CALL_LIMIT = 50;

#define ull unsigned long long
int N, M, ev[MAX_N];
std::vector<int> edge[MAX_N];
std::set<std::pair<int, int> > edge_all, edge_rep;

void FAIL(std::string s){
	std::cout << s << std::endl;
	exit(0);
}

void Report(int a, int b) {
	if (a > b) std::swap(a, b);
	if (edge_rep.count(std::make_pair(a, b))) {
		FAIL("Report called twice for one edge");
	}
	if (!edge_all.count(std::make_pair(a, b))) {
		FAIL("Reported edge does not exist");
	}
	edge_rep.insert(std::pair<int,int>(a, b));
}

std::vector<ull> Query(std::vector<ull> weight, std::vector<int> edges) {
	static bool enabled[MAX_N];
	static int call_cnt = 0;
	if (++call_cnt > CALL_LIMIT) {
		FAIL("Call of query exceeded the limitation");
	}
	if (weight.size() != N) {
		FAIL("Size of weight must be equal to N");
	}
	std::fill_n(enabled + 1, M, false);
	for (int i = 0;i < edges.size(); i ++){
		if (enabled[ edges[i] ]) {
			FAIL("Elements in edges must be unique");
		}
		enabled[ edges[i] ] = true;
	}
	std::vector<ull> res;
	for (int i = 1; i <= N; i++) {
		ull t = 0;
		for (int j = 0;j < edge[i].size(); j ++){
			if (enabled[ edge[i][j] ]) {
				t ^= weight[(i ^ ev[ edge[i][j] ]) - 1];
			}
		}
		res.push_back(t);
	}
	return res;
}

int main(){
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		if (u > v) std::swap(u, v);
		edge_all.insert(std::pair<int,int>(u, v));
		ev[i] = u ^ v;
		edge[u].push_back(i); edge[v].push_back(i);
	}
	Solve(N, M);
	if (edge_all != edge_rep) {
		FAIL("Some edges are not reported");
	}
	std::cout << "Correct" << std::endl;
}
#undef ull