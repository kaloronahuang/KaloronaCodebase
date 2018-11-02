#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int limit;
	int n;
	cin>>limit;
	cin>>n;
	int jew[n];
	for(int index=0;index<n;index++)
	{
		cin>>jew[index];
	}
	sort(jew,jew+n);
	
	int total = 0;
	int stepRec = n-1;
	for(int i = 0;i<n;i++)
	{
		
		for(;stepRec>i;stepRec--)
		{
			if(jew[stepRec]+jew[stepRec]<limit)
			{
				total++;
				stepRec--;
				break;
			}
			else
			{
				total++;
			}
		}
	}
	
	cout<<total-1;
	
	return 0;
}
