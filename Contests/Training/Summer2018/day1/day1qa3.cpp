#include <iostream>
using namespace std;
// Stuck
int main()
{
	int N =10;
	int arr[N];
	for(int index = 0;index < N;index++){
		cin>>arr[index];
	}	
	
	for(int i = 0;i<N-1;i++)
	{
		int standard = arr[i+1];
		
		for(int j = i;j>-1;j--)
		{
			if(standard<arr[j])
			{
				arr[j+1] = arr[j];
				arr[j] = standard;
			}
		}
	}
	
	for(int k = 0;k<N;k++)
	{
		cout<<arr[k]<<" ";
	}
	
	return 0;
}
