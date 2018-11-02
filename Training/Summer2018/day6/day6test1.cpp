#include <iostream>
#include <stack>
#include <cstring>
#include <vector>

using namespace std;

struct edge
{
	int to;
	int next;	
};

int main()
{
	int v,e;
	cin>>v>>e;
	int vex[v];
	memset(vex,-1,sizeof(vex));
	int indeg[v]={0};
	edge edges[e];
	int lastSrc = 0;
	int lastPos = -1;
	for(int i = 0;i<e;i++)
	{
		int src,dst;
		cin>>src>>dst;
		
		if(src != lastSrc)
			lastPos = -1;
		
		edges[i].to = dst - 1;
		edges[i].next = lastPos;
		vex[src - 1] = i;
		
		lastPos = i;
		lastSrc = src;
		
		indeg[dst-1]++;
	}
	
	// topo sort;
	
	stack<int> st;
	for(int i = 0;i<v;i++)
	{
		if(indeg[i] == 0)
			st.push(i);
	}
	int cnt = 0;
	vector<int> rec;
	while(!st.empty())
	{
		int current = st.top();
		st.pop();
		rec.push_back(current);
		
		int i = vex[current];
		if(i != -1) 
			for(;;)
			{
				if(--indeg[edges[i].to] == 0)
					st.push(edges[i].to);
				cnt++;
				if(edges[i].next == -1)
					break;
				i = edges[i].next;
			}
	}
	if(cnt < e)
	{
		cout<<"has circle";
	}
	else
	{
		for(int i = 0;i<rec.size();i++)
		{
			cout<<rec[i]+1<<" ";
		}
	}
	return 0;
}
