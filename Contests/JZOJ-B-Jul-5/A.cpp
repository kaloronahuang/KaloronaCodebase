// A.cpp
#include <bits/stdc++.h>

using namespace std;

int n, seq[2020];

int main()
{
	while(scanf("%d", &n) && n != 0)
	{
		while(scanf("%d", &seq[1]) && seq[1] != 0)
		{
			for(int i = 2; i <= n; i++)
				scanf("%d", &seq[i]);
			bool ans = true;
			stack<int> st;
			int header = 0, cur = 1;	
			while(header <= n)
			{
				if(!st.empty() && st.top() == seq[cur])
					st.pop(), cur++;
				else
					st.push(++header);
			}
			ans = (cur == n + 1);
			printf(ans ? "Yes\n" : "No\n");
		}
		puts("");
	}
	return 0;
}
