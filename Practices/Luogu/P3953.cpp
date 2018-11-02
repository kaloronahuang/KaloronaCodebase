// P3953.cpp
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

typedef unsigned long long ll;

int points[100000];
int sides[200000];
int degrees[200000];
int next[200000];
int stackPos = 0;

int startPos = 1;
int endPos;
int N,M,K,P;

void init()
{
	memset(points,-1,sizeof(points));
	memset(sides,-1,sizeof(sides));
	memset(degrees,-1,sizeof(degrees));
	memset(next,-1,sizeof(next));
}

void buildMap()
{
	cin>>N>>M>>K>>P;
	endPos = N;
	for(int i = 0;i<M;i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		int lastSide = points[a];
		sides[stackPos] = b;
		degrees[stackPos] = c;
		next[stackPos] = lastSide;
		points[a] = stackPos;
		stackPos++;
	}
}

void getShortestPath()
{
	ll p_arr[N+1];
	memset(p_arr,1000000000,sizeof(p_arr));
	queue<int> pointAwaiting
	pointAwaiting.push(1);
	while(!pointAwaiting.empty())
	{
		int pNum = pointAwaiting.size();
		for(int i = 0;i<pNum;i++)
		{
			
		}
	}
}

int main()
{
	return 0;
}
