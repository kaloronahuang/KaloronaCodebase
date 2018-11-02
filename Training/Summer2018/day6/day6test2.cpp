#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

struct edge
{
	int to = 0;
	int next = -1;
};

int main()
{
	int N,M;
	cin>>N>>M;
	int vs[N];
	memset(vs,-1,sizeof(vs));
	edge es[M];
	int indeg[N];
	memset(indeg,0,sizeof(indeg));
	
	// Input;
	int lastPos = -1;
	int lastSrc = -1;
	for(int i = 0;i<M;i++)
	{
		int src,dst;
		cin>>src>>dst;
		
		es[i].to = dst - 1;
		
		if(src!=lastSrc)
			lastPos = -1;
		es[i].next = lastPos;
		lastPos = i;
		lastSrc = src;
		vs[src-1] = i;
		indeg[dst-1]++;
	}
	
	// toposort;
	priority_queue<int,vector<int>, greater<int> > st;
	for(int i = 0;i<N;i++)
		if(indeg[i] == 0)
			st.push(i);
	
	while(!st.empty())
	{
		int current = st.top();
		cout<<current+1<<" ";
		st.pop();
		
		int i;
		if(vs[current]!=-1)
		{
			i= vs[current];
			for(;;)
			{
				if(--indeg[es[i].to] == 0) st.push(es[i].to);
				if(es[i].next == -1)	break;
				i = es[i].next;
			}
		}
			
	}
	
	return 0;
}
