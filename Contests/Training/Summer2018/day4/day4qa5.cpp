// day4 test
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

void ex5()
{
	int N;
	int logNum;
	cin>>N>>logNum;
	
	int log[N];
	for(int i = 0;i<N;i++)
	{
		cin>>log[i];
	}
	int l = 0;
	sort(log,log+N);
	for(int lenght = log[0];lenght>-1;lenght--)
	{
		int rec = 0;
		for(int i = 0;i<N;i++)
		{
			rec+=(int)floor(log[i]/lenght);
		}
		if(rec >= logNum)
		{
			l = max(l,lenght);
			break;
		}
	}
	cout<<l;
}

int main()
{
	ex5();
	return 0;
}
