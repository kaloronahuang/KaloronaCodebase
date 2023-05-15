#include <iostream>
using namespace std;

int main(){
	// Input part:
	int n;
	cin>>n;
	int arr[n];
	for(int index = 0;index<n;index++)
	{
		cin>>arr[index];
	}
	int target;
	cin>>target;
	
	// Finding part:
	for(int i=0; i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(arr[i]+arr[j]==target)
			{
				if(i<j)
				{
					cout<<i+1<<j+1;
					return 0;
				}
				else
				{
					cout<<j+1<<" "<<i+1;
					return 0;
				}
			}
		}
	}
	
	return 1;
}
