#include <iostream>
using namespace std;

int main(){
	int n;
	cin>>n;
	int A[n];
	for(int index = 0;index < n;index++)
	{
		cin>>A[index];
	}
	int standard = A[0];
	int times = 0;
	int total = 0;
	for(int i=0;i<n;i++){
		if(A[i] == standard && times < 2)
		{
			times++;
			total++;
		}
		if(A[i] != standard)
		{
			times = 1;
			total++;
			standard = A[i];
		}
	}
	cout<<total;
	return 0;
}
