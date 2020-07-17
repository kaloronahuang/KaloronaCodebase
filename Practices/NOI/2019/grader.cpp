#include "explore.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_N 200010
#define MAX_M 1000010
#define DEBUG 1

#ifdef __cplusplus
extern "C" {
#endif

#define FAIL(A...) (printf("FAIL: "), printf(A), exit(0))
#define TOKEN "Correct"

typedef struct {
	int head[MAX_N], next[MAX_M << 1], to[MAX_M << 1], tot;
}	__bgggay666_adj;

static __bgggay666_adj e, f, d;
static void append(__bgggay666_adj* e, int a, int b) {
	++e->tot; e->next[e->tot] = e->head[a]; e->to[e->tot] = b; e->head[a] = e->tot;
}
static int deg[MAX_N], cur_deg[MAX_N];
static int m_cnt, q_cnt, c_cnt;
static int m_lim, q_lim, c_lim;
static char mod[MAX_N], col[MAX_N], reported[MAX_M << 1];

void modify(int p) {
	++m_cnt;
	if(m_cnt > m_lim) FAIL("Calls of modify exceeds the limitation.\n");
	mod[p] ^= 1;
	col[p] ^= 1;
	int k;
	for(k = f.head[p]; k; k = f.next[k]) col[f.to[k]] ^= 1;
}
int query(int p) {
	++q_cnt;
	if(q_cnt > q_lim) FAIL("Calls of query exceeds the limitation.\n");
	int c = col[p];
	int k;
	for(k = f.head[p]; k; k = f.next[k]) c ^= mod[f.to[k]];
	return c;
}

static int verify(int p, int fa) {
	int k;
	for(k = f.head[p]; k; k = f.next[k])
		if(f.to[k] == fa && !reported[k])
			{reported[k] = 1; return 1;}
	return 0;
}

void report(int x, int y) {
	if(!verify(x, y) && !verify(y, x)) {
		FAIL("Wrong edge or duplicate edge: %d ~ %d.\n", x, y);
	} else {
		--cur_deg[x]; --cur_deg[y];
	}
}
int check(int x) {
	++c_cnt;
	if(c_cnt > c_lim) FAIL("Calls of check exceeds the limitation.\n");
	return !cur_deg[x];
}

int main() {
	freopen("inp.in", "r", stdin);
	e.tot = 1;
	assert(scanf("%d%d%d", &m_lim, &q_lim, &c_lim) == 3);
	int N, M, i;
	assert(scanf("%d%d", &N, &M) == 2);
	for(i = 0; i < M; ++i) {
		int a, b;
		assert(scanf("%d%d", &a, &b) == 2);
		assert(a != b);
		assert(0 <= a && a < N);
		assert(0 <= b && b < N);
		++deg[a]; ++deg[b];
		append(&e, a, b);
		append(&e, b, a);
	}
	for(i = 0; i < N; ++i) {
		cur_deg[i] = deg[i];
		append(&d, deg[i], i);
	}
	int cur_max = N - 1;
	while(cur_max) {
		int p = -1, k;
		for(k = d.head[cur_max]; k; k = d.next[k]) {
			d.head[cur_max] = k;	
			if(cur_deg[d.to[k]] == cur_max) {
				p = d.to[k];
				break;
			}
		}
		if(p == -1) {--cur_max; continue;}
		static int q[MAX_N], dfn[MAX_N], timer;
		int l = 0, r = 0, s;
		dfn[q[r++] = p] = ++timer;
		while(l != r) {
			p = q[l++];
			for(k = e.head[p]; k; k = e.next[k]) {
				s = e.to[k];
				if(s != -1 && dfn[s] != timer) {
					dfn[q[r++] = s] = timer;
					e.to[k] = -1;
					e.to[k ^ 1] = -1;
					--cur_deg[p];
					--cur_deg[s];
					append(&f, s, p);
				}
			}
			if(cur_deg[p]) append(&d, cur_deg[p], p);
		}
	}
	for(i = 0; i < N; ++i) cur_deg[i] = deg[i];
	explore(N, M);
	for(i = 0; i < N; ++i) if(cur_deg[i])
		FAIL("Not all edges are reported.\n");
	puts(TOKEN);
	if(DEBUG) fprintf(stderr, "cnt = %d/%d %d/%d %d/%d\n", m_cnt, m_lim, q_cnt, q_lim, c_cnt, c_lim);
}

#ifdef __cplusplus
}
#endif