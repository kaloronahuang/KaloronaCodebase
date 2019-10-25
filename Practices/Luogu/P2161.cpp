// P2161.cpp
#include <bits/stdc++.h>

using namespace std;

struct node
{
	int l, r;
	bool operator<(const node& nd) const { return r < nd.l; }
};

int n;
set<node> st;
set<node>::iterator it; 
char opt[10];

int main()
{
	scanf("%d", &n);
	while (n--)
	{
		int l, r, ret = 0;
		scanf("%s", opt + 1);
		if (opt[1] == 'A')
		{
			scanf("%d%d", &l, &r);
			node curt = node{l, r};
			it = st.find(curt);
			while (it != st.end())
				ret++, st.erase(it), it = st.find(curt);
			printf("%d\n", ret), st.insert(curt);
		}
		else
			printf("%lld\n", st.size());
	}
	return 0;
}
