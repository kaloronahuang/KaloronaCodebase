// day3 qa 3 4 5 15
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

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

void ex3()
{
	int m,n;
	cin>>m;
	list<int> l;
	for(int x = 0;x<m;x++)
	{
		int data;
		cin>>data;
		l.push_back(data);
	}
	cin>>n;
	for(int y = 0;y<n;y++)
	{
		int data;
		cin>>data;
		l.push_back(data);
	}
	l.sort();
	if((m+n)%2 == 0)
	{
		cout<<((float)getbit(l,(m+n)/2 - 1)+(float)getbit(l,(m+n)/2))/2;
	}
	else
	{
		cout<<((float)getbit(l,(m+n+1)/2 - 1));
	}
}

bool ex4()
{
	int n;
	cin>>n;
	int steps[n];
	for(int g = 0;g<n;g++)
		cin>>steps[g];
	int i = 0;
	for(;;)
	{
		if(i>=n)
			return true;
		if(steps[steps[i]+i]==0)
			return false;
		i+=steps[i];
	}
}

struct Worker
{
	int startTime = 0;
	int endTime = 0;
};

bool sorting(Worker a, Worker b)
{
	if(a.startTime<b.startTime)
		return true;
	else if(a.startTime == b.startTime)
		return (a.endTime<b.endTime);
	else
		return false;
}

void ex5()
{
	int workerNum;
	cin>>workerNum;
	Worker ws[workerNum];
	for(int i = 0;i<workerNum;i++)
		cin>>ws[i].startTime>>ws[i].endTime;
	sort(ws,ws+workerNum,sorting);
	
	bool sw = false;
	Worker start,last;
	start = ws[0];
	list<int> timepoint;
	int timeTotal = 0;
	for(int g = 0;g<workerNum;g++)
	{
		if(workerNum!=workerNum - 1)
		{
			if(ws[g].endTime>ws[g+1].startTime)
			{
				sw = true;
				last = ws[g+1];
			}
			else
			{
				if(sw)
				{ 
					sw = false;
					timepoint.push_back(start.startTime);
					timepoint.push_back(last.endTime);
					int temp = last.endTime - start.startTime;
					timeTotal = max(temp,timeTotal);
					start = ws[g];
					timeTotal = max(ws[g].endTime - ws[g].startTime,timeTotal);
				} 
				else
				{
					timepoint.push_back(ws[g].startTime);
					timepoint.push_back(ws[g].endTime);
					timeTotal = max(ws[g].endTime - ws[g].startTime,timeTotal);
					start = ws[g+1];
				}
			}
		}
		else
		{
			if(start.endTime<=ws[g].startTime)
			{
				timeTotal = max(ws[g].endTime - start.startTime,timeTotal);
				timepoint.push_back(start.startTime);
				timepoint.push_back(ws[g].endTime);
			}
			else
			{
				timeTotal = max(ws[g].endTime - ws[g].startTime,timeTotal);
				timepoint.push_back(ws[g].startTime);
				timepoint.push_back(ws[g].endTime);
			}
		}
	}
	cout<<timeTotal<<" ";
	int sm = 0;
	int counter = 0;
	for(;;)
	{
		if(counter>=timepoint.size())
			break;
		
		if(counter!=0)
			sm = max(getbit(timepoint,counter) - getbit(timepoint,counter-1),sm);
		else
			sm = max(getbit(timepoint,counter),sm);
		counter+=2;
	}
	cout<<sm;
}

struct appleTree
{
	int currentApples;
	int fuApples;
};

bool atcomp(appleTree a, appleTree b)
{
	return (a.fuApples<b.fuApples);
}

void ex12()
{
	int N;
	cin>>N;
	appleTree at[N];
	for(int i = 0;i<N;i++)
	{
		cin>>at[i].currentApples;
	}
	for(int i_ = 0;i_<N;i_++)
	{
		cin>>at[i_].fuApples;
	}
	sort(at,at+N,atcomp);
	
	int apples = 0;
	//apples += (at[0].currentApples);
	for(int j = 0;j<N;j++)
	{
		apples += (at[j].currentApples + at[j].fuApples * j);
	}
	
	cout<<apples;
}

void ex6()
{
	int N;
	cin>>N;
	int Ai[N];
	int Si[N];
	for(int index = 0;index< N;index++)
	{
		cin>>Si[index];
	}
	for(int index = 0;index< N;index++)
	{
		cin>>Ai[index];
	}
	
	int constantDistance = 2*Ai[N-1];
	for(int X = 1;X<N+1;X++)
	{
		int acc = 0;
		
		for(int i = N - 1;i>N-1-X;i--)
			acc += Ai[i];
		
		cout<<constantDistance + acc<<endl;
	}
}

int main()
{
	ex6();
	return 0;
}
