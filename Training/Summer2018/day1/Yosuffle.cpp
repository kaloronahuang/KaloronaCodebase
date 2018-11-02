#include <iostream>
using namespace std;

int* arr;
int count;
int pos = 0;
int M;

void Next()
{
	if(count == 0)	return;
	
	// Body
	pos = pos + M - 1;
	if(pos>count-1)
		pos = pos % (count);
	cout<<arr[pos]<<" ";
	arr[pos] = -1;
	// delete
	count--;//7
	int temp_arr[count];//7s
	int x = 0;
	bool isit = false;
	for(int i = 0;i < count;i++)
	{
		if(arr[i]==-1)
		{
			isit = true;
		}
		
		if(isit)
		{
			temp_arr[i] = arr[i+1];	
		}
		else
		{
			temp_arr[i] = arr[i];
		}
	}
	cout<<endl;
	//pos++;
	arr=temp_arr;
	Next();
}

int main(){
	int N;
	//int M;
	cin>>N;
	cin>>M;
	count = N;
	arr = new int[N];
	for(int i=0;i<=N;i++)
		arr[i] = i+1;
	Next();
	return 0;
} 
