#include <iostream>
#include <algorithm>
using namespace std;

bool comp(int a, int b)
{
	return b<a;
}

int main(){
	int arr[10];
	for (int i =0;i<10;i++)
	{
		cin>>arr[i];
	}
	sort(arr,arr+10,comp);
	for(int index=0;index<10;index++)
	{
		cout<<arr[index];
	}
	return 0;
}
