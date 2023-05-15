#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void BubleSort(){
	// declaring part:
	int arr[10]; 
	int n = 10;
	// random part:
	srand(time(NULL));
	for(int o=0;o < n;o++ )
	{
		arr[o] = rand();
	}
	// loop to compare:
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<(n-1-i);j++)
		{
			if(arr[j]<arr[j+1])
			{
				int x = arr[j];
				int y = arr[j+1];
				arr[j] = y;
				arr[j+1] = x;
			}
		}
	} 
	// output part:
	for(int index = 0;index < n;index++)
		cout<<arr[index]<<" ";
	cout<<endl;
}

void DecisionSort(){
	int n = 10;
	
	// input preperation:
	int arr[10];
 	srand(time(NULL));
 	for(int in = 0;in < 10;in++)
 	{
 		arr[in] = rand();
 		cout<<arr[in]<<" ";
 	}
 	cout<<endl;
	
	// sort:
	for(int i = 0;i<n-1;i++)
	{
		int minBias=i;
		for(int j = i+1;j<n;j++)
		{
			if(arr[j]<arr[minBias])
			{
				minBias = j;		
			}
		}
		// swap part:
		int temp = arr[i];
		arr[i] = arr[minBias];
		arr[minBias] = temp;
	}
	
	for(int index = 0; index < n; index++)
	{
		cout<<arr[index]<<" ";
	}
}

void InsertingSort(){
	int n = 10;
	
	// input preperation:
	int arr[10];
 	srand(time(NULL));
 	for(int in = 0;in < 10;in++)
 	{
 		arr[in] = rand();
 		cout<<arr[in]<<" ";
 	}
 	cout<<endl;
 	
 	// sorting part:
 	for(int i = 0;i<n-1;i++)
 	{
 		if(arr[i]<arr[i+1])
 		{
 			int standard = arr[i+1];
 			for(int j = i;j>-1;j--)
 			{
 				if(standard>arr[j])
 				{
 					arr[j+1] = arr[j];
 					arr[j] = standard; 					
 				}
 				else
 					break;
 			}
 		}
 	}
 	
 	for(int index = 0;index<n;index++)
 	{
 		cout<<arr[index]<<" ";
 	}
}
int arr[10];
void QuickSort(int arr[],int start,int end){
	int i = start;
	int j = end;
	
	int est = arr[start];
	if(i>j) return;
	while(i<j)
	{
		while(i<j&&arr[j]>est)
			j--;
		while(i<j&&arr[i]<est)
			i++;
		if(i<j)
			swap(arr[j],arr[i]);
	}
	swap(est,arr[i]);
	QuickSort(arr,start,i-1);
	QuickSort(arr,i+1, end);
}

int main(){
	int n=10;
	for(int i = 0;i<n;i++)
	{
		cin>>arr[i];
	}
	QuickSort(arr,0,n-1);
	for (int index = 0;index<n;index++)
		cout<<arr[index]<<" ";
 	return 0;
} 
