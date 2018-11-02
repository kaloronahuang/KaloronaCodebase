#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

struct point
{
	int x;
	int y;
};

bool compare(point a,point target)
{
	return (target.x == a.x && target.y == a.y);
}

bool isOnCircle(point center, int R, point p)
{
	// (x-p.x)^2 + (y-p.y)^2 = R^2;
	int maxV = sqrt(pow(R,2) - pow(center.x-p.x,2)) + p.y;
	int minV = -1 * sqrt(pow(R,2) - pow(center.x-p.x,2)) + p.y;
	return (p.y>=minV) && (p.y<=maxV);
}

int main()
{
	int N,M,R;
	cin>>N>>M>>R;
	vector<point> p;
	int counter = 0;
	for(int i = 0;i<M;i++)
	{
		int x,y;
		cin>>x>>y;
		// generate points;
		for(int xpos = x - R;xpos<=x+R;xpos++)
		{
			for(int ypos = y - R;ypos<=y+R;ypos++)
			{
				if(isOnCircle)
					if(xpos>=0 && xpos<= N && ypos >=0 && ypos <=N)
					{
						counter++;
						point pp;
						pp.x= xpos;
						pp.y=ypos;
						p.push_back(pp);
					}
			}
		}
	}
	point ps[p.size()];
	copy(p.begin(),p.end(),ps);
	int comp = 0;
	for(int i = 0;i<p.size();i++)
	{
		for(int j = 0;j<p.size();j++)
		{
			if(i!=j)
				if(compare(ps[i],ps[j]))
					comp++;
		}
	}
	cout<<counter - 2 - comp;
}
