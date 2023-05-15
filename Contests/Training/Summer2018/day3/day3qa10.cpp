// day4qa9
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
	int n,m,k,w,r;
	cin>>n>>m>>k>>w>>r;
	
	int Ai[n];
	for(int i = 0;i<n;i++)
		cin>>Ai[i];
	sort(Ai,Ai+n);
	int bias = 0;
	int tower = floor(m/k);
	for(int i = 0;i<r;i++)
	{
		bool toBreak = false;
		// time;
		for(int t = 0;t<tower;t++)
		{
			// attack;
			Ai[bias] -= w;
			if(Ai[bias] <=0)
				bias++;
			if(bias>=n)
			{
				toBreak = true;
				break;
			}
		}
		if(toBreak)
			break;
	}
	int counter = 0;
	for(int i = 0;i<n;i++)
	{
		if(Ai[i]>0) counter++;
	}
	cout<<counter;
}
