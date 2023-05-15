#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int getbit(list<int> arr, int bias)
{
	int counter = 0;
	for(list<int>::iterator it = arr.begin();it!=arr.end();it++)
	{
		if(bias == counter)
			return *it;
		counter++;
	}
}

int main()
{
	int N,M;
	int wi[N];
	cin>>N>>M; 
	for(int i = 0;i<N;i++)
		cin>>wi[i];
	if(N<M)
	{
		sort(wi,wi+N);
		cout<<wi[N-1];
		return 0;
	}
	
	int tapQ[M];
	for(int i = 0;i<M;i++)
	{
		tapQ[i] = wi[i];
	}
	
	for(int i = M;i<N;i+=M)
	{
		sort(wi+i,wi+i+M);
		sort(tapQ,tapQ+M);
		for(int j = 0;j<M;j++)
		{
			wi[0] += wi[7-j+i+M-1];
			sort(tapQ,tapQ+M);
		}
	}
	
	cout<<tapQ[M-1];
} 
