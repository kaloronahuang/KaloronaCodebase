#include <iostream>
using namespace std;

#include <ctime>
#include <cstdlib>

int main(){
	int n;
	cin>>n;
	int arr[n];
	// random part;
	srand(time(NULL));
	for(int i = 0;i<n;i++)
	{
		arr[i] = rand()%1000+1;
		cout<<arr[i]<<" ";	
	}
	cout<<endl;
	
	// delete part;
	for(int index = 0;index<n;index++)
	{
		if(index!=-1)
			for(int j = 0;j<n;j++)
			{
				if(index!=j && arr[index] == arr[j] && arr[j]!=-1)
				{
					arr[j] == -1;
				}
			}
	}
	// sort;
	// using bubble;
	for(int x = 0;x<n-1;x++)
	{
		for(int y=0;y<n-1-x;y++)
		{
			if(arr[y]>arr[y+1])
			{
				swap(arr[y],arr[y+1]);
			}
		}
	}
	// print;
	for(int count = 0;count<n;count++)
	{
		if(arr[count]!=-1)
		{
			cout<<arr[count]<<" ";
		}
	}
}
