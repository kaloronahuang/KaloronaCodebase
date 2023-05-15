#include <iostream>
#include <algorithm> 
using namespace std;

struct Point{
	int x;
	int y;
};

int main(){
	int num;
	cin>>num;
	Point ps[num];
	for(int i = 0;i<num;i++)
	{
		cin>>ps[i].x;
		cin>>ps[i].y;
	}
	int steps = 100000000;
	int ymin;
	int xs[num];
	for(int y = 10000;y>=-10000;y--)
	{
		int temp_steps = 0;
		for(int f = 0;f<num;f++)
		{
			Point currentP = ps[f];
			xs[f] = currentP.x;
			temp_steps+=abs(currentP.y-y);
		}
		if(temp_steps<steps)
		{
			steps=temp_steps;
			ymin = y;
		}
	}
	sort(xs,xs+num);
	int x_steps = 10000;
	int xaxis;
	for(int x = 10000;x>-10001;x--)
	{
		int sub = 0;
		for(int j = 0;j<num;j++)
		{
			sub += abs(xs[j]-(x+j));
		}	
		if(sub<x_steps)
		{
			x_steps = sub;
			xaxis = x;
		}
	}
	cout<<(x_steps+steps)<<endl;
	return 0;
}
