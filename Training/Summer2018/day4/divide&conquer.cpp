// divide & conquer;
#include <iostream>
#include <cmath>

using namespace std;

struct cell
{
	int* seg;
	int num;
};

int* merge(int arra[], int arrb[], int a, int b)
{
	int temp[a+b];
	int bias_a = 0;
	int bias_b = 0;
	int counter = 0;
	
	for(;bias_a<a || bias_b<b;)
	{
		if(bias_b == b)
		{
			temp[counter] = arra[bias_a];
			bias_a++;
			counter++;
			continue;
		}
		if(bias_a == a)
		{
			temp[counter] = arrb[bias_b];
			bias_b++;
			counter++;
			continue;
		}
		if(arra[bias_a]>arrb[bias_b])
		{
			temp[counter] = arrb[bias_b];
			bias_b++;
		}
		else
		{
			temp[counter] = arra[bias_a];
			bias_a++;
		}
		counter++;
	}
	
	return temp;
}

cell* mergingSort(cell c[],int N)
{
	cell temp[(int)ceil(N/2)];
	for(int i = 0;i<N-1;i+=2)
	{
		int total = c[i].num+c[i+1].num;
		temp[i/2].seg = merge(c[i].seg,c[i+1].seg,c[i].num,c[i+1].num);
		cout<<"Segs:";
		for(int j = 0;j<total;j++)
			cout<<temp[i/2].seg[j]<<endl;
		temp[i/2].num = total;
	}
	if(N/2 == 1)
		return temp;
	else
		mergingSort(temp,N/2);
}

int main()
{
	int N;
	cin>>N;
	cell arr[N];
	int segst[N];
	for(int i = 0;i<N;i++)
	{
		cin>>segst[i];
		arr[i].num = 1; 
		arr[i].seg = &segst[i];
	}
	
	cell* res = mergingSort(arr,N);
	/*for(int i = 0;i<N;i++)
	{
		cout<<res[0].seg[i];
	}*/
	
	return 0;
}
