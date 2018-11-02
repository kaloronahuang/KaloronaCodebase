#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

struct element
{
	int to = 0;
	int next = -1;
};

int main()
{
	int pnum,edgeNum;
	cin>>pnum>>edgeNum;
	int vex[pnum];
	int indeg[edgeNum];
	memset(indeg,0,sizeof(indeg));
	memset(vex,-1,sizeof(vex));
	element edges[edgeNum];
	int lastSrc = 1;
	int lastNext = -1;
	for(int i = 0;i<edgeNum;i++)
	{
		int src,dst;
		cin>>src>>dst;
		edges[i].to = dst-1;
		vex[src-1] = i;
		
		if(src != lastSrc)
		{
			lastNext = -1;
		}
		lastSrc = src;
		vex[src-1] = i;
		edges[i].next = lastNext;
		lastNext = i;
		
		// calc indegree;
		indeg[dst-1]++;
	}
	
	//for(int x=0;x<pnum;x++)
	//	cout<<vex[x]<<" ";
	
	/* // output
	for(int x = 0;x<pnum;x++)
	{
		cout<<x+1;
		for(int i = vex[x];i>=0;i--)
		{
			//if(edges[i].next == -1)
			//	break;
			cout<<" ->"<<edges[i].to;
			if(edges[i].next == -1)
				break;
		}
		cout<<endl; 
	}
	*/
	
	// topology sort;
	stack<int> sq;
	
	// get 0 indeg;
	for(int i = 0;i<pnum;i++)
	{
		if(indeg[i] == 0)
			sq.push(i);
	}
	while(!sq.empty())
	{
		int current = sq.top();
		cout<<current+1<<"->";
		sq.pop();
		int i = vex[current];
		if(i!=-1)
			for(;;)
			{
				indeg[edges[i].to]--;
				
				if(indeg[edges[i].to] == 0)
					sq.push(edges[i].to); 
				if(edges[i].next == -1)
					break;
				i = edges[i].next;
			}
	}
	return 0;
} 
