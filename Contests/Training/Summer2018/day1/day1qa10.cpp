#include <iostream>
using namespace std;

int main()
{
	int num;
	cin>>num;
	int indecies[num];
	int ti[num];
	for(int index = 0;index<num;index++)
	{
		cin>>ti[index];
		indecies[index] = index;
	}
	
	for(int i = 0;i<num-1;i++)
	{
		for(int j = 0;j<num-1-i;j++)
		{
			if(ti[j]>ti[j+1])
			{
				swap(ti[j],ti[j+1]);
				swap(indecies[j],indecies[j+1]);
			}
		}
	}
	int total = 0;
	for(int hk = 0;hk<num;hk++)
	{
		total += ((num-hk)*ti[hk]);
		cout<<ti[hk]<<" ";
	}
	cout<<(total/num);
	return 0;
}
