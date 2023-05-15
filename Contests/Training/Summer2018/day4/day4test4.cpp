#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

struct stuff
{
	int c;
	int v;
};

bool comp(stuff a, stuff b)
{
	return (a.v<b.v);
}

// 二维数组型 
/*
int main()
{
	// total pack;
	int N;
	cin>>N;
	stuff st[N];
	int volu = 10;
	
	for(int vpos = 0;vpos<N;vpos++)
		cin>>st[vpos].v;
	for(int cpos = 0;cpos<N;cpos++)
		cin>>st[cpos].c;
		
	sort(st,st+N,comp);
	// pack;
	int table[N+1][volu+1];
	memset(table,0,sizeof(table));
	for(int i = 1;i<N+1;i++)
	{
		stuff current = st[i-1];
		for(int j = 0;j<volu+1;j++)
		{
			if(j>=current.v)
			{
				table[i][j] = max(table[i-1][j],table[i][j-current.v]+current.c);
			}
			else
			{
				table[i][j] = table[i-1][j];
			}
		}
	}
	cout<<table[N][volu];
	return 0;
}
*/
// 一维数组
int main()
{
	// total pack;
	int N;
	cin>>N;
	stuff st[N];
	int volu = 10;
	
	for(int vpos = 0;vpos<N;vpos++)
		cin>>st[vpos].v;
	for(int cpos = 0;cpos<N;cpos++)
		cin>>st[cpos].c;
		
	sort(st,st+N,comp);
	
	int table[volu+1];
	memset(table,0,sizeof(table));
	
	for(int i = 0;i<N;i++)
	{
		for(int j = 0;j<volu+1;j++)
		{
			if(st[i].v<=j)
			{
				table[j] = max(table[j],table[j-st[i].v]+st[i].c);
			}
		}
	}
	
	cout<<table[volu];
	return 0;
} 
