#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

struct coin
{
	int v;
	int c;
};

bool comp(coin a, coin b)
{
	return a.v<b.v;
}

int main()
{
	int W,N;
	cin>>W>>N;
	
	coin cs[N];
	int table[W+1];
	memset(table,0,sizeof(table));
	for(int i = 0;i<N;i++)
	{
		cin>>cs[i].v>>cs[i].c;
	}
	
	sort(cs,cs+N,comp);
	
	for(int i = 0;i<N;i++)
	{
		for(int j = 0;j<W+1;j++)
		{
			if(j>=cs[i].v)
			{
				table[j] = max(table[j],table[j - cs[i].v] + cs[i].c);
			}
		}
	}
	
	cout<<table[W];
}
