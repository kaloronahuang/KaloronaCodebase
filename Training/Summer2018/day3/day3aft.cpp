// day3aft
#include <iostream>
#include <algorithm>
#include <string>
#include <numeric>
#include <list>
#include <cmath>

using namespace std;

void HalfSearch()
{
	int L,N,M;
	cin>>L>>N>>M;
	int nodes[N];
	int dis[N+1];
	int dis_[N+1];
	for(int index = 0;index<N;index++)
	{
		if(index == 0)
		{
			cin>>nodes[index];
			dis[index] = nodes[index];
			dis_[index] = nodes[index];
		}
		else
		{
			int num;
			cin>>num;
			nodes[index] = num;
			dis[index] = num - nodes[index-1];
			dis_[index] = num - nodes[index-1];
		}
	}
	dis[N] = L - nodes[N-1];
	// simplify;
	sort(dis,dis+N+1);
	int counter = 0;
	for(int c = 0;c<M;c++)
	{
		for(int j = 0;j<N+1;j++)
		{
			if(dis[c] == dis_[j])	
			{
				dis_[j] = 0;
				nodes[j] = 0;
				break;
			}
		}
	}
	// recalculate;
	int distances[N+1-M];
	int last = 0;
	int co = 0;
	for(int i = 0;i<M;i++)
	{
		if(nodes[i]!=0)
		{
			distances[co] = nodes[i] - last;
			last = nodes[i];
			co++;
		}
	}
	distances[co] = L - last;
	sort(distances,distances + N +1-M);
	
	for(int j = 0;j<M;j++)
		cout<<nodes[j]<<" ";
	
	cout<<distances[M];
}

int getbit(list<int> l,int bias)
{
	int i = 0;
	for(list<int>::iterator it = l.begin();it!=l.end();it++)
	{
		if(i == bias)
			return *it;
		i++;
	}
}

float getbitf(list<float> l,int bias)
{
	int i = 0;
	for(list<float>::iterator it = l.begin();it!=l.end();it++)
	{
		if(i == bias)
			return *it;
		i++;
	}
}

void stones()
{
	int L,N,M;
	cin>>L>>N>>M;
	
	list<int> nodes;
	list<int> distances;
	list<int> changedDis;
	
	for(int index = 0;index<N;index++)
	{
		int d;
		cin>>d;
		nodes.push_back(d);
		if(index == 0)
		{
			distances.push_back(d);
			changedDis.push_back(d);
		}
		else
		{
			distances.push_back(d - getbit(nodes,index-1));
			changedDis.push_back(d - getbit(nodes,index - 1));
		}
	}
	
	distances.push_back(L - getbit(nodes,N-1));
	changedDis.push_back(L - getbit(nodes,N-1));
	
	changedDis.sort();
	int standard = getbit(changedDis,M);
	
	int counter = 0;
	
	list<int> removing_stuff;
	
	for(int i = 0;i<N+1 && counter < M;i++)
	{
		if(getbit(distances,i)<=standard)
		{
			if(i != nodes.size())
			{
				int hc = getbit(nodes,i);
				removing_stuff.push_back(hc);
				counter++;
				//nodes.remove(hc);
			}
			else
			{
				int hc = getbit(nodes,i-1);
				removing_stuff.push_back(hc);
				counter++;
				//nodes.remove(hc);
			}
		}
	}
	
	for(int v = 0;v<removing_stuff.size();v++)
		nodes.remove(getbit(removing_stuff,v));
	
	list<int> dises;
	for(int j = 0;j<nodes.size();j++)
	{
		if(j==0)
		dises.push_back(getbit(nodes,j));
		else
		dises.push_back(getbit(nodes,j) - getbit(nodes,j - 1));
	}
	dises.push_back(L - getbit(nodes,nodes.size()-1));
	dises.sort();
	
	cout<<getbit(dises,0);
}

void watering()
{
	int m;
	cin>>m;
	for(int g = 0;g<m;g++)
	{
		int N;
		cin>>N;
		list<float> water;
		list<float> longs;
		for(int i = 0;i<N;i++)
		{
			float r;
			cin>>r;
			if(r<=1)
				continue;
			water.push_back(r);
			longs.push_back(2*sqrt((pow(r,2)-1)));
		}
		longs.sort();
		float total = 0;
		int totaltimes = 0;
		for(int j = longs.size()-1;j>-1;j--)
		{
			total+=getbitf(longs,j);
			totaltimes++;
			if(total>=20)
     				break;
		}
		cout<<totaltimes;
	}
}

struct activity
{
	int start;
	int end;
};

bool isOccupied(activity a, activity b)
{
	if(a.start<=a.end)
		return true;
}

bool comp(activity a, activity b)
{
	return (a.end < b.end);
}

void activityArrangement()
{
	int testset;
	cin>>testset;
	for(int m = 0;m<testset;m++)
	{
		int n;
		cin>>n;
		activity act[n];
		int earliest =24;
		
		for(int g = 0;g<n;g++)
		{
			cin>>act[g].start;
			cin>>act[g].end;
		}
		sort(act,act+n,comp);
		
		int activities = 1;
		activity comparing = act[0];
		for(int i = 1;i<n;i++)
		{
			if(act[i].start>comparing.end)
			{
				activities++;
				comparing = act[i];
			}
			//	activities++;
		}
		
		cout<<activities;
	}
}

int main()
{
	activityArrangement();
	return 0;
}
