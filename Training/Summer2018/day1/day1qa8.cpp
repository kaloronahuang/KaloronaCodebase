#include <iostream>
using namespace std;
#include <algorithm>

int N;
int K;

int abs(int i)
{
	if(i>0 || i==0)
	return i;
	else
	return -1 * i;
}

int getMin(int* nums,int excp)
{
	int total;
	for(int i = 0;i<N;i++)
	{
		if(i == excp)
			continue;
		int bias;
		int subtraction=0;
		for(int j = 0;j<N;j++)
		{
			if(j!=excp && j!=i && nums[j]!=-1)
			{
				if(abs(nums[i]-nums[j])<subtraction)
				{
					bias = j;
					subtraction = abs(nums[i] - nums[j]);
				}
			}
		}
		total += subtraction;
		nums[i] = -1;
		nums[bias] = -1;
	}
	return total;
}

/*
int main()
{
	cin>>N;
	cin>>K;
	int classes[N];
	for(int index = 0;index<N;index++)
	{
		cin>>classes[index];
	}
	
	int subtractions[K];
	for(int i = 0;i<K;i++)
	{
		subtractions[i] = getMin(classes,i);
	}
	sort(subtractions,subtractions+K);
	cout<<subtractions[0]; 
	return 0;
}*/
int main(){
	cin>>N;
	cin>>K;
	int classes[N];
	for(int index = 0;index<N;index++)
	{
		cin>>classes[index];
	}
	sort(classes,classes+N);
	
	for(int way = 0;way<N;way++)
	{
		
		for(int i = N-1;i>-1;i--)
		{
			
		}	
	}
}
