// theif problem;

#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	int N;
	cin>>N;
	int vol = 10;
	int table[N+1][vol+1];
	int c[N];
	int v[N];
	memset(table,0,sizeof(table));
	for(int i = 0;i<N;i++)
	{
		cin>>v[i]; 
	}
	for(int i = 0;i<N;i++)
	{
		cin>>c[i]; 
	}
	
	// sort;
	for(int i = 0;i<N-1;i++)
	{
		for(int j = 0;j<N-1-i;j++)
		{
			if(v[j]<v[j+1])
			{
				swap(v[j],v[j+1]);
				swap(c[j],c[j+1]);
			}
		}
	}
	
	// calc;
	// input to table;
	for(int i = 1;i<N+1;i++)
	{
		for(int j = 0;j<vol+1;j++)
		{
			// j is vol;
			if(v[i-1]<=j)
			{
				table[i][j] = max(table[i-1][j],table[i-1][j-v[i-1]] + c[i-1]);
			}
			else
			{
				table[i][j] = table[i-1][j];
			}
		}
	}
	cout<<table[N][vol];
	return 0;
}
