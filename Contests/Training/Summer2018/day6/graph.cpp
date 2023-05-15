#include <iostream>
#include <cstring>

using namespace std;

// Graph;

void graphIO()
{
	int nodeNum;
	cin>>nodeNum;
	int edges;
	cin>>edges;
	bool table[nodeNum][nodeNum];
	memset(table,0,sizeof(table));
	// input;
	for(int i = 0;i<edges;i++)
	{
		int src,dst;
		cin>>src>>dst;
		table[src - 1][dst - 1] = true;
	}
	// output;
	for(int x = 0;x<nodeNum;x++)
	{
		for(int y = 0;y<nodeNum;y++)
		{
			cout<<table[x][y]<<" ";
		}
		cout<<endl;
	}
}

int main()
{
	graphIO();
	return 0;
}
