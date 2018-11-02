#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main()
{
	int num;
	cin>>num;
	int acc = 0;
	vector<int> numbit;
	for(int i = 1;num/i >= 0.1;i*=10)
	{
		acc++;
		numbit.push_back((int)(((int)floor(num/i)%10)));
	}
	cout<<acc<<endl;
	for(int i = numbit.size()-1;i>-1;i--)
	{
		cout<<numbit[i]<<endl;
	}
	return 0;
}