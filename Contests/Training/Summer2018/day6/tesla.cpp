// graph
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int main()
{
	int pnum, pathNum;
	cin>>pnum>>pathNum;
	int table[pnum][pnum];
	int weights[pnum][pnum];
	memset(weights,-1,sizeof(weights));
	memset(table,-1,sizeof(table));
	for(int p = 0;p<pathNum;p++)
	{
		int src,dst;
		cin>>src>>dst;
		table[src-1][dst-1] = 1;
		table[src-1][dst-1] = 1;
		cin>>weights[src-1][dst-1];
	}
	// start point;
	int px = 0;
	int py = 0;
	int counter = 0;
	vector<int> points;
	int rec[pnum];
	memset(rec,1000000,sizeof(rec));
	rec[0] = 0;
	int final = pnum-1;
	for(;px<pnum;)
	{
		for(;py<pnum;)
		{
			if(weights[px][py] != -1 && table[px][py] == 1)
			{
				if(rec[py]>weights[px][py]+rec[px])
				{
					rec[py] = weights[px][py]+rec[px];
					points.push_back(py);
					table[px][py] = -1;
					table[py][px] = -1;
				}
			}
			py++;
		}
		//table[px][py] = -1;
		if(points.size() == 0)
			break;
		points.erase(points.begin());
		px = points.front();
		py = 0;
	}
	for(int i = 0;i<pnum;i++)
	cout<<rec[i]<<" ";
}
