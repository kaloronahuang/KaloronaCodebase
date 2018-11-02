// day2 aft
#include <iostream>
#include <cmath>

using namespace std;

int WezzoffleExample()
{
	int x,y;
	if(x>y)
		swap(x,y);
	cin>>x>>y;
	double w = (sqrt(5)+1)/2;
	int est = floor(w*(y-x));
	if(est == x)
		cout<<"Second won.";
	else
		cout<<"First win.";
	return 0;
}

int WezzoffleTest()
{
	int n,m;
	cin>>n>>m;
	double w = (sqrt(5)+1)/2;
	if(n>m)
		swap(n,m);
	int jud = floor(w * (m-n));
	if(n == jud)
		cout<<"B";
	else
		cout<<"A";
	return 0;
}

int NimmExample()
{
	int num;
	cin>>num;
	int leap[num];
	for(int index = 0;index<num;index++)
	{
		cin>>leap[index];
	}
	
	bool strangeSituation = false;
	for(int i = 0;i<num&&!strangeSituation;i++)
	{
		int total = 0;
		for(int j = 0;j<num;j++)
		{
			if(j!=i)
			{
				// xor
				if(j!=0)
					//total = total^leap[i]^leap[j];
					total^=leap[j];
				else
					//total = leap[i]^leap[j];
					total = leap[j];
			}
		}
		if(total == leap[i])
			strangeSituation = true;
	}
	
	if(strangeSituation)
		cout<<"B";
	else
		cout<<"A";
	
	return 0;
}



int main()
{
	return NimmExample();
}
