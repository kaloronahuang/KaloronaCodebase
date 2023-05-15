// dc
#include <iostream>
#include <cmath>

using namespace std;

struct block
{
	int data[500];
	int num;
};

block merge(block a,block b)
{
	int tmp[a.num+b.num];
	int apos = 0;
	int bpos = 0;
	bool aend,bend;
	int counter = 0;
	for(;;)
	{
		if(aend)
		{
			tmp[counter]=b.data[bpos];
			counter++;
			bpos++;
		}
		else if(bend)
		{
			tmp[counter]=a.data[apos];
			counter++;
			apos++;
		}
		else if(a.data[apos] <= b.data[bpos])
		{
			tmp[counter] = a.data[apos];
			apos++; 
			counter++;
		}
		else
		{
			tmp[counter] = b.data[bpos];
			bpos++;
			counter++;
		}
		if(apos == a.num)
			aend == true;
		if(bpos == a.num)
			bend == true;
		if(counter == a.num + b.num)
			break;
	}
}

block dc(block elements[],int eleNum)
{
	int counter = 0;
	//block bs[100];
	if(eleNum == 2)
		return merge(elements[0],elements[1]);
	
	block tmp[(int)ceil(eleNum/2)];
	if(eleNum % 2 != 0)
		tmp[(int)ceil(eleNum/2)] = elements[eleNum-1];
	for(int g = 0;g<eleNum;g+=2)
	{
		if(eleNum == g+1)
		{
			break;
		}
		tmp[g/2] = merge(elements[g],elements[g+1]);
	}
	return dc(tmp,counter);
}

int main()
{
	int N;
	cin>>N;
	int data[N];
	block bks[N];
	for(int i = 0;i<N;i++)
	{
		cin>>data[i];
		//int dt[1] = { data[i] };
		bks[i].num = 1;
		bks[i].data[0] = data[i];
	}
	block res = dc(bks,N);
	cout<<res.data[N-1];
	return 0;
}
