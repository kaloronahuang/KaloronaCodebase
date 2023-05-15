#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

struct stuff
{
	int volume;
	int cost;
}; 

bool comp(stuff a, stuff b)
{
	return (a.volume>b.volume);
}

int main()
{
	int N;
	cin>>N;
	int totalVol;
	cin>>totalVol;
	stuff st[N];
	
	int table[totalVol+1];
	memset(table,0,sizeof(table));
	for(int i = 0;i<N;i++)
	{
		cin>>st[i].volume;
		//cin>>st[i].cost;
	}
	for(int i = 0;i<N;i++)
	{
		//cin>>st[i].volume;
		cin>>st[i].cost;
	}
	sort(st,st+N,comp);
	for(int s = 0;s<N;s++)
	{
		for(int pivot = totalVol;pivot>-1;pivot--)
		{
			if(st[s].volume <= pivot)
			{
				table[pivot] = max(st[s].cost + table[pivot - st[s].volume], table[pivot]);
			}
		}
	}
	cout<<table[totalVol];
}
