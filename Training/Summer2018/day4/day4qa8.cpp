#include <iostream>

using namespace std;

int main()
{
	int M,S,T;
	cin>>M>>S>>T;
	
	int totalDistance = 0;
	int totalTimeframe = 0;
	bool isEscaped = false;
	for(;;)
	{
		if(totalTimeframe == T)
			break;
		if(M>=10)
		{
			totalDistance+=60;
			totalTimeframe++;
			if(totalDistance >= S)
			{
				isEscaped = true;
				break;
			}
			M-=10;
		}
		else
		{
			if(T-totalTimeframe == 1)
			{
				totalTimeframe++;
				totalDistance += 17;
				isEscaped = (totalDistance >= S);
				break;
			}
			if(S-totalDistance <= 17)		
			{
				totalTimeframe++;
				totalDistance += 17;
				isEscaped = true;
				break;
			}
			else
			{
				// rest;
				M+=4;
				totalTimeframe++;
			}
		} 
	}
	if(isEscaped)
	{
		cout<<"Yes"<<endl;
		cout<<totalTimeframe;
	}
	else
	{
		cout<<"No"<<endl;
		cout<<totalDistance;
	}
}
